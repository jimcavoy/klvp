/// @file Implementation file for KLVParser
#include "klvprsr.h"
#include "util.h"

#include <cstdint>
#include <cstring>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif

static const uint8_t UniversalMetadataElementKey[] = { 0x06, 0x0E, 0x2B, 0x34, 0x01 };

uint64_t ntohll(uint64_t Value);
uint64_t htonll(uint64_t Value);

/////////////////////////////////////////////////////////////////////////////
// KLVParser::Impl


namespace lcss
{
    /// @brief Implementation class of KLVParser
    class KLVParser::Impl
    {
    public:
        enum class STATE : int {
            START_SET_KEY,
            START_SET_LEN_FLAG,
            START_SET_LEN,
            LEXING,
            PARSING
        };

    public:
        void onEndKey(TYPE type);
        void onEndSetKey();
        void onEndLenFlag();
        void onBegin(KLVParser& parser, int len) const;

    public:
        STATE					state_{ lcss::KLVParser::Impl::STATE::START_SET_KEY };
        TYPE					type_{ lcss::TYPE::UNKNOWN };
        std::vector<uint8_t>	pbuffer_;
        int						setsize_{ 0 };

        bool					validateChecksum_{ false };
        std::vector<uint8_t>	sodb_;  // sequence of data bytes
        lcss::KLVElement		checksumElement_;
    };

    void KLVParser::Impl::onEndKey(TYPE type)
    {
        type_ = type;
        onEndSetKey();
    }

    void KLVParser::Impl::onEndSetKey()
    {
        state_ = lcss::KLVParser::Impl::STATE::START_SET_LEN_FLAG;
        pbuffer_.clear();
    }

    void KLVParser::Impl::onEndLenFlag()
    {
        state_ = lcss::KLVParser::Impl::STATE::START_SET_LEN;
        pbuffer_.clear();
    }

    void KLVParser::Impl::onBegin(KLVParser& parser, int len) const
    {
        switch (type_)
        {
        case TYPE::LOCAL_SET: parser.onBeginSet(len, type_); break;
        case TYPE::UNIVERSAL_SET: parser.onBeginSet(len, type_); break;
        case TYPE::SECURITY_UNIVERSAL_SET: parser.onBeginSet(len, type_); break;
        case TYPE::UNIVERSAL_ELEMENT: parser.onBeginSet(len, type_); break;
        case TYPE::UNKNOWN: parser.onBeginSet(len, type_); break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// KLVParser

lcss::KLVParser::KLVParser()
    : _pimpl(std::make_unique<lcss::KLVParser::Impl>())
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

/// @brief Parse a MISB ST 0601 encoded stream in @p buffer.
/// @param buffer [in] The buffer containing a MISB ST 0601 stream.
void lcss::KLVParser::parse(const gsl::span<uint8_t> buffer)
{
    for (const uint8_t& b : buffer)
    {
        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_KEY)
        {
            _pimpl->pbuffer_.push_back(b);
            if (_pimpl->pbuffer_.size() == 16)
            {
                if (std::equal(_pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end(), LocalSetKey))
                {
                    _pimpl->sodb_.insert(_pimpl->sodb_.begin(), _pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end());
                    _pimpl->onEndKey(TYPE::LOCAL_SET);
                }
                else if (std::equal(_pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end(), UniversalMetadataSetKey))
                {
                    _pimpl->sodb_.insert(_pimpl->sodb_.begin(), _pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end());
                    _pimpl->onEndKey(TYPE::UNIVERSAL_SET);
                }
                else if (std::equal(_pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end(), SecurityMetadataUniversalSetKey))
                {
                    _pimpl->sodb_.insert(_pimpl->sodb_.begin(), _pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end());
                    _pimpl->onEndKey(TYPE::SECURITY_UNIVERSAL_SET);
                }
                else if (std::equal(_pimpl->pbuffer_.begin(), _pimpl->pbuffer_.begin() + 4, UniversalMetadataElementKey))
                {
                    _pimpl->sodb_.insert(_pimpl->sodb_.begin(), _pimpl->pbuffer_.begin(), _pimpl->pbuffer_.end());
                    _pimpl->onEndKey(TYPE::UNIVERSAL_ELEMENT);
                }
                else
                {
                    onError("Failed to parse group key\n", 0);
                    return;
                }
            }
        }
        else if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_LEN_FLAG)
        {
            _pimpl->onEndLenFlag();
            // handle boundary case when length bytes cross over two input buffer arguments
            _pimpl->pbuffer_.push_back(b);
        }
        else if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_LEN)
        {
            const int lenFlag = getLenFlag(_pimpl->pbuffer_[0]);
            int setsz = 0;
            if (lenFlag == 0)
            {
                setsz = _pimpl->pbuffer_[0];
                _pimpl->sodb_.push_back(_pimpl->pbuffer_[0]);
                _pimpl->onBegin(*this, setsz);
            }
            else if (_pimpl->pbuffer_.size() == lenFlag + 1)
            {
                uint8_t lengthFlag = lenFlag | 0x80;
                _pimpl->sodb_.push_back(lengthFlag);
                auto first = _pimpl->pbuffer_.begin();
                ++first; // skip over the length flag
                _pimpl->sodb_.insert(_pimpl->sodb_.end(), first, _pimpl->pbuffer_.end());
                setsz = getKLVSetSize(_pimpl->pbuffer_.data() + 1, lenFlag);
                _pimpl->onBegin(*this, setsz);
            }
            else
                _pimpl->pbuffer_.push_back(b);
        }

        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::LEXING)
        {
            _pimpl->pbuffer_.push_back(b);
            _pimpl->sodb_.push_back(b);
            if (_pimpl->pbuffer_.size() == _pimpl->setsize_)
            {
                _pimpl->state_ = lcss::KLVParser::Impl::STATE::PARSING;
            }
        }

        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::PARSING)
        {
            int n = 0;
            while (n < _pimpl->setsize_)
            {
                KLVElement klv;
                if (_pimpl->type_ == TYPE::LOCAL_SET)
                {
                    n += klv.parse(_pimpl->pbuffer_.data() + n, _pimpl->setsize_);
                }
                else
                {
                    if (_pimpl->type_ == TYPE::UNIVERSAL_ELEMENT)
                        n += klv.parseUniversalSetElement(_pimpl->sodb_.data() + n, _pimpl->setsize_);
                    else
                        n += klv.parseUniversalSetElement(_pimpl->pbuffer_.data() + n, _pimpl->setsize_);
                }
                onElement(klv);
            }
            onEndSet();
        }
    }
}

/// @brief The KLVParser instance calls this function when starting to parse a KLV Set.
/// Override this function to extend its behavior for your context.  Ensure to call
/// the parent function lcss::KLVParser::onBeginSet in your override function.
/// @param len [in] The KLV Set size in bytes excluding the 16 byte Set tag and length bytes.
/// @param type [in] The KLV Set type.  See @ref lcss::TYPE "lcss::TYPE" enumeration. 
void lcss::KLVParser::onBeginSet(int len, TYPE type)
{
    _pimpl->setsize_ = len;
    _pimpl->state_ = lcss::KLVParser::Impl::STATE::LEXING;
    _pimpl->pbuffer_.clear();
}

/// @brief The KLVParser calls this function when completing parsing a KLV element.  
/// Override this function to extent its behavior for your context.  Ensure to call the 
/// parent function lcss::KLVParser::onElement in your override function.
/// @param klv [in] The KLVElement instance that was parsed.
void lcss::KLVParser::onElement(lcss::KLVElement& klv)
{
    if (klv.key() == 1)
        _pimpl->checksumElement_ = klv;
}

/// @brief The KLVParser calls this function when finishing parsing a KLV set.
/// Override this function to extent its behavior for your context.  Ensure to call the 
/// parent function lcss::KLVParser::onEndSet in your override function.
void lcss::KLVParser::onEndSet()
{
    _pimpl->state_ = lcss::KLVParser::Impl::STATE::START_SET_KEY;
    _pimpl->setsize_ = 0;
    _pimpl->pbuffer_.clear();
    if (isValidating() && _pimpl->type_ == TYPE::LOCAL_SET)
    {
        if (_pimpl->checksumElement_.key() != 1)
        {
            onError("Invalid Checksum", 0);
        }
        else
        {
            uint8_t val[2]{};
            unsigned short cs = 0;
            _pimpl->checksumElement_.value(val);
            memcpy(&cs, val, 2);
            unsigned short localCs = ntohs(cs);
            if (bcc_16(_pimpl->sodb_.begin(), _pimpl->sodb_.end() - 2) != localCs)
            {
                onError("Invalid Checksum", 0);
            }
        }
    }
    _pimpl->sodb_.clear();
}

/// @brief The KLVParser call this function when parsing error occurs. 
///  Override this function to extent its behavior for your context.  Ensure to call the 
/// parent function lcss::KLVParser::onError in your override function.
/// @param errmsg [in] The error message
/// @param pos [in] The position in the byte stream where the error is located.
void lcss::KLVParser::onError(const char* errmsg, int pos)
{
    _pimpl->state_ = lcss::KLVParser::Impl::STATE::START_SET_KEY;
    _pimpl->setsize_ = 0;
    _pimpl->pbuffer_.clear();
    _pimpl->sodb_.clear();
}

/// @brief Call this function to determine if the KLVParser is validating the KLV set checksum.
/// By default KLV set checksum validation is disable (false).
/// @return Returns true if the KLVParser instance is validating the KLV set checksum, otherwise false.
bool lcss::KLVParser::isValidating() const noexcept
{
    return _pimpl->validateChecksum_;
}

/// @brief Enable or disable checksum validation while parsing. 
/// By default KLV set checksum validation is disable (false).
/// If checksum validation fails, the KLVParser will call KLVParser::onError.
/// @param val [in] Set to true to enable KLV set checksum validation, otherwise false to disable.
void lcss::KLVParser::validateChecksum(bool val) noexcept
{
    _pimpl->validateChecksum_ = val;
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
        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_KEY)
        {
            if (b != 0x30)
                return;
            else {
                _pimpl->sodb_.push_back(0x30);
                _pimpl->onEndKey(TYPE::LOCAL_SET);
            }
        }
        else if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_LEN_FLAG)
        {
            _pimpl->onEndLenFlag();
            // handle boundry case when length bytes cross over two input buf arguments
            _pimpl->pbuffer_.push_back(b);
        }
        else if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::START_SET_LEN)
        {
            const int lenFlag = getLenFlag(_pimpl->pbuffer_[0]);
            int setsz = 0;
            if (lenFlag == 0)
            {
                setsz = _pimpl->pbuffer_[0];
                _pimpl->sodb_.push_back(_pimpl->pbuffer_[0]);
                onBeginSet(setsz, TYPE::LOCAL_SET);
            }
            else if (_pimpl->pbuffer_.size() == lenFlag + 1)
            {
                uint8_t lengthFlag = lenFlag | 0x80;
                _pimpl->sodb_.push_back(lengthFlag);
                auto first = _pimpl->pbuffer_.begin();
                ++first; // skip over the length flag
                _pimpl->sodb_.insert(_pimpl->sodb_.end(), first, _pimpl->pbuffer_.end());
                setsz = getKLVSetSize(_pimpl->pbuffer_.data() + 1, lenFlag);
                onBeginSet(setsz, TYPE::LOCAL_SET);
            }
            else
                _pimpl->pbuffer_.push_back(b);
        }

        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::LEXING)
        {
            _pimpl->pbuffer_.push_back(b);
            _pimpl->sodb_.push_back(b);
            if (_pimpl->pbuffer_.size() == _pimpl->setsize_)
            {
                _pimpl->state_ = lcss::KLVParser::Impl::STATE::PARSING;
            }
        }

        if (_pimpl->state_ == lcss::KLVParser::Impl::STATE::PARSING)
        {
            int n = 0;
            while (n < _pimpl->setsize_)
            {
                KLVElement klv;
                n += klv.parseSecuritySetElement(_pimpl->pbuffer_.data() + n, _pimpl->setsize_);
                onElement(klv);
            }
            onEndSet();
        }
    }
}

