#ifndef KLVELMT_H
#define KLVELMT_H

#include <memory>

#include <loki/Visitor.h>
#include <string>
#include <cstdint>

namespace lcss
{
	class KLVElementImpl;

/////////////////////////////////////////////////////////////////////////////
// KLVElement
// KLVElement is a handle class
class KLVElement
{
public:
	friend bool operator==(const KLVElement& lhs, const KLVElement& rhs);
	friend bool operator!=(const KLVElement& lhs, const KLVElement& rhs);
	friend bool operator<(const KLVElement& lhs, const KLVElement& rhs);
	friend bool operator>(const KLVElement& lhs, const KLVElement& rhs);
	friend bool operator>=(const KLVElement& lhs, const KLVElement& rhs);
	friend bool operator<=(const KLVElement& lhs, const KLVElement& rhs);
public:
	KLVElement();
	KLVElement(uint8_t key);
	KLVElement(const uint8_t* key, int size);
	virtual ~KLVElement();
	KLVElement(const KLVElement& orig);
	KLVElement(KLVElement&& src) noexcept; 
	KLVElement& operator=(const KLVElement& rhs);
	KLVElement& operator=(KLVElement&& rhs) noexcept;

	void swap(KLVElement& src);

	void Accept(Loki::BaseVisitor& visitor);

	/// <summary>
	/// Returns the decoded key value for a KLV element 
	/// (i.e. non BER-OID).  
	/// Call key(uint8_t*) to retrieve the BER-OID form
	/// </summary>
	/// <returns>Key value &gt; 0 and value &lt; 256</returns>
	uint8_t key() const;

	/// <summary>
	/// Retrieve KLV element's key in the serialized BER-OID form.
	/// </summary>
	/// <param name="key">The buffer to hold the serialized bytes</param>
	/// <returns>The number of bytes to hold the key. If input parameter is null
	/// return the number of bytes without filling input parameter.</returns>
	int key(uint8_t* key) const;

	int length() const;

	/// <summary>
	/// Returns the number of bytes used to encode the length field
	/// using BER encoding.
	/// Ref: MISB ST 0107.3, Section 6.3.2, 1 November 2018
	/// </summary>
	/// <returns>Number of bytes used to BER encoded the length; otherwise,
	///  return 0 for error.</returns>
	int numOfBytesForLength() const;

	void value(uint8_t*) const;
	uint8_t* value();
	void setValue(uint8_t* newVal, int size);

	int parse(uint8_t* buf, int size);

	int parseSecuritySetElement(uint8_t* buf, int size);

	int parseUniversalSetElement(uint8_t* buf, int size);

	int serialize(uint8_t* buf, int bufsz);

	void* appData();

	void setAppData(void* appData);
private:
	int compare(const KLVElement& element) const;
private:
	std::shared_ptr<KLVElementImpl> pimpl_;
};

///////////////////////////////////////////////////////////////////////////////
// Free function comparison operators
inline bool operator==(const KLVElement& lhs, const KLVElement& rhs)
{
	return lhs.compare(rhs) == 0;
}

inline bool operator!=(const KLVElement& lhs, const KLVElement& rhs)
{
	return lhs.compare(rhs) != 0;
}

inline bool operator>(const KLVElement& lhs, const KLVElement& rhs)
{
	return lhs.compare(rhs) > 0;
}

inline bool operator<(const KLVElement& lhs, const KLVElement& rhs)
{
	return lhs.compare(rhs) < 0;
}

inline bool operator>=(const KLVElement& lhs, const KLVElement& rhs)
{
	return (lhs.compare(rhs) > 0 || lhs.compare(rhs) == 0);
}

inline bool operator<=(const KLVElement& lhs, const KLVElement& rhs)
{
	return (lhs.compare(rhs) < 0 || lhs.compare(rhs) == 0);
}

} // lcss

#endif