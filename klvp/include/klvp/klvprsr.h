#ifndef KLVPRSR_H
#define KLVPRSR_H

#include "klvelmt.h"

#include <memory>
#include <gsl/gsl>

namespace lcss
{
	/// @brief KLV Set types
	enum class TYPE : int {
		LOCAL_SET, ///< Local set
		UNIVERSAL_SET, ///< Universal set
		SECURITY_UNIVERSAL_SET,  ///< Universal security set
		UNIVERSAL_ELEMENT, ///< Universal element
		UNKNOWN ///< Unknown set type
	};

/////////////////////////////////////////////////////////////////////////////
// KLVParser

	/// @brief Inherit KLVParser to parse a MISB ST 0601 encoded stream.
	class KLVParser
	{	
	public:
		KLVParser(); ///< Default constructor
		virtual ~KLVParser(); ///< class destructor

		virtual void parse(const gsl::span<const uint8_t> buffer);

		virtual void onBeginSet( int len, TYPE type);
		virtual void onElement( lcss::KLVElement& klv);
		virtual void onEndSet();

		virtual void onError(const char* errmsg, int pos);

		bool isValidating() const noexcept;
		void validateChecksum(bool val) noexcept;

	protected:
		class Impl; ///< KLVParser implementation class
		std::unique_ptr<Impl> _pimpl; ///< smart pointer the KLVParser implementation class
	};

/////////////////////////////////////////////////////////////////////////////
// KLVSecuritySetParser

	/// @brief Inherit KLVSecuritySetParser to parse a MISB ST 0102 encoded 
	/// stream.
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