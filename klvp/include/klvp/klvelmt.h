#ifndef KLVELMT_H
#define KLVELMT_H

/// @file klvelmt.h
///
/// The KLVElement class definition file.

#include <memory>

#include <loki/Visitor.h>
#include <string>
#include <cstdint>

namespace lcss
{
	class KLVElementImpl;

/////////////////////////////////////////////////////////////////////////////
// KLVElement

/// @brief KLVElement is a handle class that reference its implementation in
/// a body class KLVElementImpl.
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

	/// @brief Accept an instance of a Visitor class.  See Visitor Pattern.
	/// @param visitor [in, out] An instance of a Visitor class.
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

	/// @brief The number of bytes of the value.
	/// @return Returns the number of bytes used to encode a value.
	int length() const;

	/// <summary>
	/// Returns the number of bytes used to encode the length field
	/// using BER encoding.
	/// Ref: MISB ST 0107.3, Section 6.3.2, 1 November 2018
	/// </summary>
	/// <returns>Number of bytes used to BER encoded the length; otherwise,
	///  return 0 for error.</returns>
	int numOfBytesForLength() const;

	/// @brief Get the encoded value.
	/// @param value [in, out] Copy the value into the buffer.  Ensure the buffer size is sufficient to hold the bytes being copied.
	void value(uint8_t* value) const;

	/// @brief Get the encoded value.
	/// @return Returns a pointer to the value.
	uint8_t* value();

	/// @brief Set the value of a KLVElement instance.
	/// @param newVal [in] The new value passed as byte array in @p newVal,
	/// @param size [in] The size of the byte array passed in as @p newVal.
	void setValue(uint8_t* newVal, int size);

	/// @brief Parse the buffer to create a KLVElement
	/// @param buf [in] The raw KLV encoded stream
	/// @param size [in] The size of the KLV stream @p buf.
	/// @return Return the number of bytes read.
	int parse(uint8_t* buf, int size);

	/// @brief 
	/// @param buf 
	/// @param size 
	/// @return 
	int parseSecuritySetElement(uint8_t* buf, int size);

	/// @brief 
	/// @param buf 
	/// @param size 
	/// @return 
	int parseUniversalSetElement(uint8_t* buf, int size);

	/// @brief Serialize the KLVElement to a byte array.
	/// @param buf [in, out] The byte array passed in by the client code to hold the serialize KLV encoding.
	/// @param bufsz [in] The size of the passed in byte array, @p buf
	/// @return Returns the number of bytes that was serialized to the byte array passed in by @p buf. 
	int serialize(uint8_t* buf, int bufsz);

	void* appData();

	void setAppData(void* appData);
private:
	int compare(const KLVElement& element) const;
private:

	/// @brief smart pointer to the class implementation (body) class.
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