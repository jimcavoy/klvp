#pragma once

#include <loki/Visitor.h>
#include "klvelmtimpl.h"

namespace lcss
{
	class UniversalMetadataElement
		:public KLVElementImpl
	{
	public:
		UniversalMetadataElement(uint8_t* key);
		virtual ~UniversalMetadataElement();
		LOKI_DEFINE_VISITABLE()
	};
}