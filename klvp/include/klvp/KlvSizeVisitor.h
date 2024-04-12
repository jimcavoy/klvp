/// @file KlvSizeVisitor.h
#pragma once

#include "klvelmtimpl.h"
#include "klvuselmtimpl.h"
#include "klvsselmtimpl.h"

#include <loki/Visitor.h>

namespace lcss
{
	/// @brief KlvSizeVisitor resets the length field in a KLV group instance.
	class KlvSizeVisitor :
		public Loki::BaseVisitor,
		public Loki::Visitor<lcss::UniversalMetadataElement>,
		public Loki::Visitor<lcss::UASElement>,
		public Loki::Visitor<lcss::KLVSetElement>,
		public Loki::Visitor<lcss::KLVSecurityElement>,
		public Loki::Visitor<lcss::KLVUnknown>,
		public Loki::Visitor<lcss::KLVUnknownSecurity>
	{
	public:
		KlvSizeVisitor();
		virtual ~KlvSizeVisitor();

		void Visit(lcss::UASElement& element) override;
		void Visit(lcss::UniversalMetadataElement& grp) override;
		void Visit(lcss::KLVSetElement& grp) override;
		void Visit(lcss::KLVSecurityElement& item) override;
		void Visit(lcss::KLVUnknown& item) override;
		void Visit(lcss::KLVUnknownSecurity& item) override;

		int size_;		 ///< Total Size
		int secSetSize_; ///< Security Set Size
	};
}
