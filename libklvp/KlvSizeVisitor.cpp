#include "KlvSizeVisitor.h"

#include "util.h"

namespace
{
	int encodedBERLengthSize(int len)
	{
		if (len < 128) {
			return 1;
		}
		else if (len > 127 && len < 256) {
			return 2;
		}
		else if (len > 255 && len < 65536) {
			return 3;
		}
		return 0;
	}
}

KlvSizeVisitor::KlvSizeVisitor()
	: size_(0), 
	secSetSize_(0) 
{
}

KlvSizeVisitor::~KlvSizeVisitor()
{
}

void KlvSizeVisitor::Visit(lcss::UASElement& item)
{
	size_++; // key 
	size_ += item.numOfBytesForLength(); // length size
	size_ += item.length();
}


void KlvSizeVisitor::Visit(lcss::KLVUnknown& item)
{
	int sz = item.key(NULL);
	size_ += sz; // key 
	size_ += item.numOfBytesForLength(); // length size
	size_ += item.length();
}

void KlvSizeVisitor::Visit(lcss::KLVUnknownSecurity& item)
{
	int sz = item.key(NULL);
	secSetSize_ += sz; // key 
	secSetSize_ += item.numOfBytesForLength(); // length size
	secSetSize_ += item.length();
}

void KlvSizeVisitor::Visit(lcss::UniversalMetadataElement& grp)
{
	uint8_t key[16];
	grp.key(key);

	if (lcss::isLDSGroup(key, 16))
	{
		int* pSize = new int(size_ + secSetSize_);
		grp.setAppData((void*)pSize);
	}
}

void KlvSizeVisitor::Visit(lcss::KLVSetElement& grp)
{
	size_++; // key 
	size_ += encodedBERLengthSize(secSetSize_); // length size
	int* pSize = new int(secSetSize_);
	grp.setAppData((void*)pSize);
}

void KlvSizeVisitor::Visit(lcss::KLVSecurityElement& item)
{
	secSetSize_++; // key 
	secSetSize_ += item.numOfBytesForLength(); // length size
	secSetSize_ += item.length();
}

