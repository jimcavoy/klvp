#pragma once

#include <vector>
#include <memory>

#define MAX_DATA 512

/// <summary>
/// 
/// </summary>
struct ValidValue
{
	ValidValue();
	~ValidValue();
	ValidValue(const ValidValue& orig);
	ValidValue& operator=(const ValidValue& rhs);

	void swap(ValidValue& orig);

	char displayName[MAX_DATA];
	char value[MAX_DATA];
	char codingMethod[MAX_DATA];
};


/// <summary>
/// 
/// </summary>
struct LDSEntry
{
	typedef std::vector<ValidValue> valueCollection;
	typedef valueCollection::iterator iterator;

	LDSEntry();
	LDSEntry(const LDSEntry& orig);
	LDSEntry& operator=(const LDSEntry& rhs);
	LDSEntry(LDSEntry&& orig) noexcept;
	LDSEntry& operator=(LDSEntry&& rhs) noexcept;
	~LDSEntry();

	void swap(LDSEntry& orig);

	unsigned int  key;
	unsigned int  length;
	unsigned char permission;

	char	name[MAX_DATA];
	char	units[MAX_DATA];
	char	format[MAX_DATA];
	char	description[MAX_DATA];

	valueCollection validValues;
};

/// <summary>
/// 
/// </summary>
class LDSDatabase
{
public:
	LDSDatabase();
	~LDSDatabase();

	LDSDatabase(LDSDatabase&&) noexcept;
	LDSDatabase(const LDSDatabase&) = delete;

	LDSDatabase& operator=(LDSDatabase&&) noexcept;
	LDSDatabase& operator=(LDSDatabase&) = delete;

	bool connect(const char* databaseFilePath);
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
	void create_sqlstmt(char* stmt, size_t sz, const LDSEntry& entry);
	void create_security_sqlstmt(char* stmt, size_t sz, const LDSEntry& entry);
	/// <summary>
	/// Fetches the security elements.
	/// </summary>
	/// <param name="backInsertIt">The back inserter iterator.</param>
	/// <returns></returns>
	template<class T> size_t fetch_security_elements(T backInsertIt);

private:
	class Impl;
	std::unique_ptr<Impl> _pimpl;
};

