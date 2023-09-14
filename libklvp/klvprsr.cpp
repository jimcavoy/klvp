#include "klvprsr.h"

#include "klvelmtimpl.h"

#include <cstdint>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif

uint64_t ntohll ( uint64_t Value );
uint64_t htonll ( uint64_t Value );

const uint8_t lcss::LocalSetKey[] = { 0x06,0x0E,0x2B,0x34,
	0x02,0x0B,0x01,0x01,
	0x0E,0x01,0x03,0x01,
	0x01,0x00,0x00,0x00 };

const uint8_t lcss::SecurityMetadataUniversalSetKey[] = { 0x06,0x0E,0x2B,0x34,
0x02,0x01,0x01,0x01,
0x02,0x08,0x02,0x00,
0x00,0x00,0x00,0x00 };


const uint8_t lcss::UniversalMetadataSetKey[] = { 0x06,0x0E,0x2B,0x34,
0x02,0x01,0x01,0x01,
0x0E,0x01,0x01,0x02,
0x01,0x01,0x00,0x00 };

static const uint8_t UniversalMetadataElementKey[] = { 0x06, 0x0E, 0x2B, 0x34, 0x01 };

class IsChecksum
	:public Loki::BaseVisitor,
	public Loki::Visitor<lcss::KLVChecksum>
{
public:
	IsChecksum() :flag_(false) {}

	void Visit(lcss::KLVChecksum& klv)
	{
		flag_ = true;
	}

	bool flag_;
};

namespace
{
	bool isEnd(lcss::KLVElement& klv)
	{
		IsChecksum vis;
		klv.Accept(vis);

		return vis.flag_;
	}

	// Ref: MISB ST 0601.8, 23 October 14, page 12
	template<typename T>
	unsigned short bcc_16(T first, T last)
	{
		// Initialize Checksum and counter variables.
		unsigned short bcc = 0;
		unsigned short i = 0;
		T it;
		// Sum each 16-bit chunk within the buffer into a checksum
		for (it = first; it != last; ++it, i++)
			bcc += *it << (8 * ((i + 1) % 2));
		return bcc;
	} // end of bcc_16 ()
}

/////////////////////////////////////////////////////////////////////////////
// KLVParser

lcss::KLVParser::KLVParser()
	:state_(lcss::KLVParser::STATE::START_SET_KEY)
	, setsize_(0)
	, validateChecksum_(false)
	, type_(TYPE::UNKNOWN)
{

}

lcss::KLVParser::~KLVParser()
{

}



static int getLenFlag(uint8_t len)
{
	// retrieve length
	// get the number of bytes
	if ((int)len < 128)
		return 0;
	uint8_t size = len ^ 0x80;
	return size;
}

static int getKLVSetSize(const uint8_t* stream, int sz)
{
	int ret = 0;
	if (sz < 2)
	{
		uint8_t len = 0;
		memcpy(&len, stream, sz);
		ret = len;
	}
	else if (sz < 3)
	{
		int len = 0;
		memcpy(&len, stream, sz);
		ret = ntohs(len);
	}
	else if (sz < 4)
	{
		int len = 0;
		memcpy(&len, stream, sz);
		ret = ntohl(len);
		ret = ret >> 5;
	}
	else if (sz < 5)
	{
		int len = 0;
		memcpy(&len, stream, sz);
		ret = ntohl(len);
	}

	return ret;
}

void lcss::KLVParser::parse(const gsl::span<const uint8_t> buffer)
{
	for (const uint8_t& b : buffer)
	{
		if (state_ == lcss::KLVParser::STATE::START_SET_KEY)
		{
			pbuffer_.push_back(b);
			if (pbuffer_.size() == 16)
			{
				if (std::equal(pbuffer_.begin(), pbuffer_.end(), LocalSetKey))
				{
					sodb_.insert(sodb_.begin(), pbuffer_.begin(), pbuffer_.end());
					onEndKey(TYPE::LOCAL_SET);
				}
				else if (std::equal(pbuffer_.begin(), pbuffer_.end(), UniversalMetadataSetKey))
				{
					sodb_.insert(sodb_.begin(), pbuffer_.begin(), pbuffer_.end());
					onEndKey(TYPE::UNIVERSAL_SET);
				}
				else if (std::equal(pbuffer_.begin(), pbuffer_.end(), SecurityMetadataUniversalSetKey))
				{
					sodb_.insert(sodb_.begin(), pbuffer_.begin(), pbuffer_.end());
					onEndKey(TYPE::SECURITY_UNIVERSAL_SET);
				}
				else if (std::equal(pbuffer_.begin(), pbuffer_.begin() + 4, UniversalMetadataElementKey))
				{
					sodb_.insert(sodb_.begin(), pbuffer_.begin(), pbuffer_.end());
					onEndKey(TYPE::UNIVERSAL_ELEMENT);
				}
				else
				{
					onError("Failed to parse group key\n", 0);
					return;
				}
			}
		}
		else if (state_ == lcss::KLVParser::STATE::START_SET_LEN_FLAG)
		{
			onEndLenFlag();
			// handle boundry case when length bytes cross over two input buf arguments
			pbuffer_.push_back(b);
		}
		else if (state_ == lcss::KLVParser::STATE::START_SET_LEN)
		{
			const int lenFlag = getLenFlag(pbuffer_[0]);
			int setsz = 0;
			if (lenFlag == 0)
			{
				setsz = pbuffer_[0];
				sodb_.push_back(pbuffer_[0]);
				onBegin(setsz);
			}
			else if (pbuffer_.size() == lenFlag + 1)
			{
				uint8_t lengthFlag = lenFlag | 0x80;
				sodb_.push_back(lengthFlag);
				auto first = pbuffer_.begin();
				++first; // skip over the length flag
				sodb_.insert(sodb_.end(), first, pbuffer_.end());
				setsz = getKLVSetSize(pbuffer_.data() + 1, lenFlag);
				onBegin(setsz);
			}
			else
				pbuffer_.push_back(b);
		}

		if (state_ == lcss::KLVParser::STATE::LEXING)
		{
			pbuffer_.push_back(b);
			sodb_.push_back(b);
			if (pbuffer_.size() == setsize_)
			{
				state_ = lcss::KLVParser::STATE::PARSING;
			}
		}

		if (state_ == lcss::KLVParser::STATE::PARSING)
		{
			int n = 0;
			while (n < setsize_)
			{
				KLVElement klv;
				if (type_ == TYPE::LOCAL_SET)
				{
					n += klv.parse(pbuffer_.data() + n, setsize_);
				}
				else
				{
					if (type_ == TYPE::UNIVERSAL_ELEMENT)
						n += klv.parseUniversalSetElement(sodb_.data() + n, setsize_);
					else
						n += klv.parseUniversalSetElement(pbuffer_.data() + n, setsize_);
				}
				onElement(klv);
			}
			onEndSet();
		}
	}
}

void lcss::KLVParser::onEndKey(TYPE type)
{
	type_ = type;
	onEndSetKey();
}

void lcss::KLVParser::onBegin(int len)
{
	switch (type_)
	{
	case TYPE::LOCAL_SET: onBeginSet(len, type_); break;
	case TYPE::UNIVERSAL_SET: onBeginSet(len, type_); break;
	case TYPE::SECURITY_UNIVERSAL_SET: onBeginSet(len, type_); break;
	case TYPE::UNIVERSAL_ELEMENT: onBeginSet(len, type_); break;
	}
}


void lcss::KLVParser::onEndSetKey()
{
	state_ = lcss::KLVParser::STATE::START_SET_LEN_FLAG;
	pbuffer_.clear();
}

void lcss::KLVParser::onEndLenFlag()
{
	state_ = lcss::KLVParser::STATE::START_SET_LEN;
	pbuffer_.clear();
}

void lcss::KLVParser::onBeginSet(int len, TYPE type)
{
	setsize_ = len;
	state_ = lcss::KLVParser::STATE::LEXING;
	pbuffer_.clear();
}

void lcss::KLVParser::onElement(lcss::KLVElement& klv)
{
	if (klv.key() == 1)
		checksumElement_ = klv;
}

void lcss::KLVParser::onEndSet()
{
	state_ = lcss::KLVParser::STATE::START_SET_KEY;
	setsize_ = 0;
	pbuffer_.clear();
	if (validateChecksum_ && type_ == TYPE::LOCAL_SET)
	{
		if (checksumElement_.key() != 1)
		{
			onError("Invalid Checksum", 0);
		}
		else
		{
			uint8_t val[2]{};
			unsigned short cs = 0;
			checksumElement_.value(val);
			memcpy(&cs, val, 2);
			unsigned short localCs = ntohs(cs);
			if (!(bcc_16(sodb_.begin(), sodb_.end() - 2)) == localCs)
			{
				onError("Invalid Checksum", 0);
			}
		}
	}
	sodb_.clear();
}

void lcss::KLVParser::onError(const char* errmsg, int pos)
{
	state_ = lcss::KLVParser::STATE::START_SET_KEY;
	setsize_ = 0;
	pbuffer_.clear();
	sodb_.clear();
}

/////////////////////////////////////////////////////////////////////////////
// KLVSecuritySetParser
lcss::KLVSecuritySetParser::KLVSecuritySetParser()
{

}

lcss::KLVSecuritySetParser::~KLVSecuritySetParser()
{

}

void lcss::KLVSecuritySetParser::onEndSet()
{

}

void lcss::KLVSecuritySetParser::parse(const gsl::span<uint8_t> buffer)
{
	for (const uint8_t& b : buffer)
	{
		if (state_ == lcss::KLVParser::STATE::START_SET_KEY)
		{
			if (b != 0x30)
				return;
			else {
				sodb_.push_back(0x30);
				onEndKey(TYPE::LOCAL_SET);
			}
		}
		else if (state_ == lcss::KLVParser::STATE::START_SET_LEN_FLAG)
		{
			onEndLenFlag();
			// handle boundry case when length bytes cross over two input buf arguments
			pbuffer_.push_back(b);
		}
		else if (state_ == lcss::KLVParser::STATE::START_SET_LEN)
		{
			const int lenFlag = getLenFlag(pbuffer_[0]);
			int setsz = 0;
			if (lenFlag == 0)
			{
				setsz = pbuffer_[0];
				sodb_.push_back(pbuffer_[0]);
				onBeginSet(setsz, TYPE::LOCAL_SET);
			}
			else if (pbuffer_.size() == lenFlag + 1)
			{
				uint8_t lengthFlag = lenFlag | 0x80;
				sodb_.push_back(lengthFlag);
				auto first = pbuffer_.begin();
				++first; // skip over the length flag
				sodb_.insert(sodb_.end(), first, pbuffer_.end());
				setsz = getKLVSetSize(pbuffer_.data() + 1, lenFlag);
				onBeginSet(setsz, TYPE::LOCAL_SET);
			}
			else
				pbuffer_.push_back(b);
		}

		if (state_ == lcss::KLVParser::STATE::LEXING)
		{
			pbuffer_.push_back(b);
			sodb_.push_back(b);
			if (pbuffer_.size() == setsize_)
			{
				state_ = lcss::KLVParser::STATE::PARSING;
			}
		}

		if (state_ == lcss::KLVParser::STATE::PARSING)
		{
			int n = 0;
			while (n < setsize_)
			{
				KLVElement klv;
				n += klv.parseSecuritySetElement(pbuffer_.data() + n, setsize_);
				onElement(klv);
			}
			onEndSet();
		}
	}
}