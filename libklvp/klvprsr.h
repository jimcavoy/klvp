#ifndef KLVPRSR_H
#define KLVPRSR_H

#include "klvelmt.h"

#include <vector>
#include <memory>
#include <gsl/gsl>

namespace lcss
{
	extern const uint8_t LocalSetKey[16];
	extern const uint8_t UniversalMetadataSetKey[16];
	extern const uint8_t SecurityMetadataUniversalSetKey[16];

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

// Template function to calculate checksum
// Ref: MISB ST 0601.14a, 1 May 2020, page 31
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

#endif