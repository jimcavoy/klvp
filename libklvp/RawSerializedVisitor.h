#pragma once

#include "klvelmtimpl.h"
#include "klvuselmtimpl.h"
#include "klvsselmtimpl.h"
#include "util.h"

#include "loki/Visitor.h"

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// RawSerializeVisitor
class RawSerializeVisitor :
	public Loki::BaseVisitor,
	public Loki::Visitor<lcss::UniversalMetadataElement>,
	public Loki::Visitor<lcss::UASElement>,
	public Loki::Visitor<lcss::KLVSetElement>,
	public Loki::Visitor<lcss::KLVSecurityElement>,
	public Loki::Visitor<lcss::KLVUnknown>,
	public Loki::Visitor<lcss::KLVUnknownSecurity>
{
public:
	RawSerializeVisitor(std::vector<uint8_t>& rawByteSeq)
		:_archive(rawByteSeq)
	{
	}

	void Visit(lcss::UniversalMetadataElement& item) override
	{
		uint8_t key[16];
		item.key(key);

		if (lcss::isLDSGroup(key, 16))
		{
			doVisitSet(item);
		}
	}

	void Visit(lcss::UASElement& item) override
	{
		doVisitElement(item);
	}

	void Visit(lcss::KLVUnknown& item) override
	{
		doVisitElement(item);
	}


	void Visit(lcss::KLVSecurityElement& item) override
	{
		doVisitElement(item);
	}

	void Visit(lcss::KLVUnknownSecurity& item) override
	{
		doVisitElement(item);
	}

	void Visit(lcss::KLVSetElement& grp) override
	{
		int len = *((int*)grp.appData());
		_archive.push_back(grp.key());

		encodeBERLength(len);
		delete grp.appData();
	}

	const uint8_t* data() noexcept
	{
		return _archive.data();
	}

private:

	void encodeBERLength(int len)
	{
		if (len < 128)
		{
			uint8_t c = (uint8_t)len;
			_archive.push_back(c);
		}
		else if (len > 127 && len < 256)
		{
			uint8_t c = 0x81;
			_archive.push_back(c);
			uint8_t sz = (uint8_t)len;
			_archive.push_back(sz);
		}
		else if (len > 255 && len < 65536)
		{
			uint8_t c = 0x82;
			_archive.push_back(c);
			UINT16 sz = htons(len);
			uint8_t s[2];
			memcpy(s, (void*)&sz, 2);
			_archive.push_back(s[0]);
			_archive.push_back(s[1]);
		}
	}

	void doVisitSet(lcss::KLVElementImpl& grp)
	{
		uint8_t key[16];
		int len = *((int*)grp.appData());

		grp.key(key);

		for (int i = 0; i < 16; ++i)
			_archive.push_back(key[i]);

		encodeBERLength(len);
		delete grp.appData();
	}

	void doVisitElement(lcss::KLVElementImpl& elmt)
	{
		uint8_t value[0x0FFF];
		int len = elmt.serialize(value, 0x0FFF);
		for (int i = 0; i < len; ++i)
			_archive.push_back(value[i]);
	}

private:
	std::vector<uint8_t>& _archive;
};