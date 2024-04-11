#pragma once

/**
* @file ldsdb.h
* 
* Header file for the LDS Database library
*/

#include <vector>
#include <memory>

#define MAX_DATA 128

/**
 * @brief ValidValue represents all the values 
 * that are assigned to a KLV entry that are consider valid, such as, Security Classification.
 */
struct ValidValue
{
	ValidValue();
	~ValidValue();
	ValidValue(const ValidValue& orig);
	ValidValue& operator=(const ValidValue& rhs);

	void swap(ValidValue& orig);

	/**
	 * @brief The display name of the valid value.
	 */
	char displayName[MAX_DATA];
	/**
	 * @brief The value of the valid value.
	 */
	char value[MAX_DATA];
	/**
	 * @brief The coding method of the valid value.
	 */
	char codingMethod[MAX_DATA];
};


/**
 * @brief LDSEntry represents one Key-Length-Value (KLV) element definition.
 */
struct LDSEntry
{
	/**
	 * @brief typedef for valid value collection
	 */
	typedef std::vector<ValidValue> valueCollection;
	/**
	 * @brief typedef for an iterator to a valid value collection
	 */
	typedef valueCollection::iterator iterator;

	LDSEntry();
	LDSEntry(const LDSEntry& orig);
	LDSEntry& operator=(const LDSEntry& rhs);
	LDSEntry(LDSEntry&& orig) noexcept;
	LDSEntry& operator=(LDSEntry&& rhs) noexcept;
	~LDSEntry();

	void swap(LDSEntry& orig);

	/**
	 * @brief The key (tag) for a KLV element.
	 */
	unsigned int  key;
	/**
	 * @brief The allowed length for the value part of a KLV element.
	 */
	unsigned int  length;
	/**
	 * @brief A bit flag property defining the Create-Read-Update-Delete (CRUD) for a KLV element.
	 * 8 = Create, 4 = Read, 2 = Update, 1 = Delete
	 */
	unsigned char permission;
	/**
	 * @brief The user friendly name for the KLV element.
	 */
	char	name[MAX_DATA];
	/**
	 * @brief The units of the value such as degrees, meters, seconds, etc.
	 */
	char	units[MAX_DATA];
	/**
	 * @brief The format to the encoded value for the KLV element.
	 */
	char	format[MAX_DATA];
	/**
	 * @brief The symbol for the KLV element.
	 */
	char	symbol[MAX_DATA];
	/**
	 * @brief A short description of the KLV element.
	 */
	char	description[MAX_DATA];

	/**
	 * @brief A collection of ValidValue instances associated with a KLV element. 
	 */
	valueCollection validValues;
};

/**
 * @brief The LDSDatabase class allow you to connect to the Sqlite3 database, klv.3db, and query its content using
 * its fetch() member functions.
 */
class LDSDatabase
{
public:
	/**
	 * @brief Default Constructor
	 */
	LDSDatabase();
	/**
	 * @brief Destructor
	 */
	~LDSDatabase();

	LDSDatabase(LDSDatabase&&) noexcept;
	LDSDatabase(const LDSDatabase&) = delete;

	LDSDatabase& operator=(LDSDatabase&&) noexcept;
	LDSDatabase& operator=(LDSDatabase&) = delete;
	
	bool connect(const char* UrlToDatabaseFile);
	void disconnect();
	bool is_open() const;
	void fetch(LDSEntry* entry);
	void fetch_security(LDSEntry* entry);
	template<class T> size_t fetch_list(T backInsertIt);
	template<class T> size_t fetch_security_list(T backInsertIt);
	template<class T> size_t fetch_security_elements_validvalues(T first, T last);

	template<class T> size_t fetch_list_rights(T backInsertIt, const char* countryCode);
	template<class T> size_t fetch_security_list_rights(T backInsertIt, const char* countryCode);

private:
	class Impl;
	std::unique_ptr<Impl> _pimpl;
};

