#ifndef KLVPRSR_H
#define KLVPRSR_H

#include "klvelmt.h"

#include <memory>
#include <gsl/gsl>

namespace lcss
{
	enum class TYPE : int {
		LOCAL_SET,
		UNIVERSAL_SET,
		SECURITY_UNIVERSAL_SET,
		UNIVERSAL_ELEMENT,
		UNKNOWN
	};

/////////////////////////////////////////////////////////////////////////////
// KLVParser
	class KLVParser
	{	
	public:
		KLVParser();
		virtual ~KLVParser();

		virtual void parse(const gsl::span<const uint8_t> buffer);

		virtual void onBeginSet( int len, TYPE type);
		virtual void onElement( lcss::KLVElement& klv);
		virtual void onEndSet();

		virtual void onError(const char* errmsg, int pos);

		bool isValidating() const noexcept;
		void validateChecksum(bool val) noexcept;

	protected:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

/////////////////////////////////////////////////////////////////////////////
// KLVSecuritySetParser
	class KLVSecuritySetParser
		:public KLVParser
	{
	public:
		KLVSecuritySetParser();
		virtual ~KLVSecuritySetParser();

		virtual void onEndSet();

		virtual void parse( const gsl::span<uint8_t> buffer);
	};
}

#endif