#ifndef KLVPRSR_H
#define KLVPRSR_H

#include "klvelmt.h"

#include <vector>
#include <gsl/gsl>

namespace lcss
{
	extern const uint8_t LocalSetKey[16];
	extern const uint8_t UniversalMetadataSetKey[16];
	extern const uint8_t SecurityMetadataUniversalSetKey[16];
/////////////////////////////////////////////////////////////////////////////
// KLVParser
	class KLVParser
	{
	protected:
		enum class STATE : int {
			START_SET_KEY,
			START_SET_LEN_FLAG,
			START_SET_LEN,
			LEXING,
			PARSING
		};

		enum class TYPE : int {
			LOCAL_SET,
			UNIVERSAL_SET,
			SECURITY_UNIVERSAL_SET,
			UNIVERSAL_ELEMENT,
			UNKNOWN
		};
	public:
		KLVParser();
		virtual ~KLVParser();

		virtual void parse(const gsl::span<const uint8_t> buffer);

		virtual void onBeginSet( int len, TYPE type);
		virtual void onElement( lcss::KLVElement& klv);
		virtual void onEndSet();

		virtual void onError(const char* errmsg, int pos);

		bool isValidating() const noexcept { return validateChecksum_;}
		void validateChecksum(bool val) noexcept { validateChecksum_ = val; }

	protected:
		void onEndKey(TYPE type);
		void onEndSetKey();
		void onEndLenFlag();
		void onBegin(int len);

	protected:
		STATE				state_;
		TYPE				type_;
		std::vector<uint8_t>	pbuffer_;
		int					setsize_;

		bool validateChecksum_;
		std::vector<uint8_t>	sodb_;  // sequence of data bytes
		lcss::KLVElement	checksumElement_;
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