#include <ldsdb/ldsdb.h>

#include <sqlite3.h>

#include <iterator>
#include <map>
#include <cstdint>
#include <cstring>

#ifndef WIN32
#define strcpy_s strcpy
#define sprintf_s sprintf
#endif


using namespace std;

const char* IDS_QUERY_VALIDVALUES = "SELECT Key, DisplayName, ValidValue, CodingMethodId FROM (SecurityLds JOIN ValidSecurityValue ON Key = KlvTag);";
const char* IDS_QUERY_RIGHTS = "SELECT KlvTag, Name, Units, Format, Length, CRUD FROM UasLds JOIN (CountryCode JOIN CountryKlvCrudAssoc ON CountryCode.ID = CountryKlvCrudAssoc.CountryCodeId) ON UasLds.Key = KlvTag WHERE ((STANAG1059_2Letters='%s') OR (STANAG1059_3Letters='%s'));";
const char* IDS_QUERY_SECURITY_RIGHTS = "SELECT KlvTag, Name, Units, Format, Length, CRUD FROM SecurityLds JOIN (CountryCode JOIN CountrySecKlvCrudAssoc ON CountryCode.ID = CountrySecKlvCrudAssoc.CountryCodeId) ON SecurityLds.Key = KlvTag WHERE ((STANAG1059_2Letters='%s')OR(STANAG1059_3Letters='%s'));";

class LDSDatabase::Impl
{
public:
	Impl() {}
	~Impl() {}

	sqlite3* _db{ nullptr };
};

LDSDatabase::LDSDatabase()
	: _pimpl{ std::make_unique<Impl>() }
{
}

LDSDatabase::~LDSDatabase()
{
	disconnect();
}

LDSDatabase::LDSDatabase(LDSDatabase&&) noexcept = default;

LDSDatabase& LDSDatabase::operator=(LDSDatabase&&) noexcept = default;

bool LDSDatabase::connect(const char* uriFilename)
{
	int rc = 0;
	char* zErrmsg = 0;

	if (_pimpl->_db == nullptr)
	{
		rc = sqlite3_open_v2(uriFilename, &_pimpl->_db, SQLITE_OPEN_READONLY | SQLITE_OPEN_URI, NULL);
		if (rc)
		{
			fprintf(stderr, "Sqlite Error: %s\n", sqlite3_errmsg(_pimpl->_db));
			disconnect();
			return false;
		}
	}
	return true;
}

void LDSDatabase::disconnect()
{
	if (_pimpl->_db != nullptr)
	{
		sqlite3_close(_pimpl->_db);
		_pimpl->_db = nullptr;
	}
}

bool LDSDatabase::is_open() const
{
	return _pimpl->_db != nullptr ? true : false;
}


void LDSDatabase::create_sqlstmt(char* stmt, size_t sz, const LDSEntry& entry)
{
	const char* select = "select Name, Units, Format, Description from UasLds where (";
#ifdef WIN32
	strcpy_s(stmt, sz, select);
#else
	strcpy(stmt, select);
#endif

	char no[6]{};
#ifdef WIN32
	strcat_s(stmt, sz, "Key=");
#else
	strcat(stmt, "Key=");
#endif

	uint16_t value = 0;
	value = (uint16_t)entry.key;
#ifdef WIN32
	sprintf_s(no, "%d", value);
	strcat_s(stmt, sz, no);
	strcat_s(stmt, sz, "\n)");
#else
	sprintf(no, "%d", value);
	strcat(stmt, no);
	strcat(stmt, "\n");
#endif

	
}

void LDSDatabase::create_security_sqlstmt(char* stmt, size_t sz, const LDSEntry& entry)
{
	const char* select = "select Name, Units, Format from SecurityLds where (";
	char no[6]{};
	uint16_t value = 0;
	value = (uint16_t)entry.key;

#ifdef WIN32
	strcpy_s(stmt, sz, select);
	strcat_s(stmt, sz, "Key=");
	sprintf_s(no, "%d", value);
	strcat_s(stmt, sz, no);
	strcat_s(stmt, sz, "\n)");
#else
	strcpy(stmt, select);
	strcat(stmt, "Key=");
	sprintf(no, "%d", value);
	strcat(stmt, no);
	strcat(stmt, "\n)");
#endif
}

static int fetch_callback(void* data, int argc, char** argv, char** azColName)
{
	LDSEntry* entry = (LDSEntry*)data;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(azColName[i], "Name") == 0)
		{
			strcpy_s(entry->name, argv[i]);
		}
		else if (strcmp(azColName[i], "Units") == 0)
		{
			strcpy_s(entry->units, argv[i]);
		}
		else if (strcmp(azColName[i], "Format") == 0)
		{
			strcpy_s(entry->format, argv[i]);
		}
		else if (strcmp(azColName[i], "Description") == 0 && argv[i] != nullptr)
		{
			strcpy_s(entry->description, argv[i]);
		}
	}
	return 0;
}

void LDSDatabase::fetch(LDSEntry* entry)
{
	char* zErrMsg = 0;
	int rc = 0;
	char cmdstr[BUFSIZ]{};
	create_sqlstmt(cmdstr, BUFSIZ, *entry);

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_callback, (void*)entry, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void LDSDatabase::fetch_security(LDSEntry* entry)
{
	char* zErrMsg = 0;
	int rc = 0;
	char cmdstr[BUFSIZ]{};
	create_security_sqlstmt(cmdstr, BUFSIZ, *entry);

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_callback, (void*)entry, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

}

/////////////////////////////////////////////////////////////////////////////
// ValidValue

ValidValue::ValidValue()
	: displayName{}
	, value{}
	, codingMethod{}
{

}

ValidValue::~ValidValue()
{

}

ValidValue::ValidValue(const ValidValue& orig)
{
	strcpy_s(displayName, orig.displayName);
	strcpy_s(value, orig.value);
	strcpy_s(codingMethod, orig.codingMethod);
}

ValidValue& ValidValue::operator=(const ValidValue& rhs)
{
	ValidValue temp(rhs);
	swap(temp);
	return *this;
}

void ValidValue::swap(ValidValue& orig)
{
	std::swap(displayName, orig.displayName);
	std::swap(value, orig.value);
	std::swap(codingMethod, orig.codingMethod);
}


/////////////////////////////////////////////////////////////////////////////
// LDSEntry

LDSEntry::LDSEntry()
	: key(0)
	, length(0)
	, permission(0x04)
	, name{}
	, units{}
	, format{}
	, description{}
{

}

LDSEntry::LDSEntry(const LDSEntry& orig)
{
	key = orig.key;
	length = orig.length;
	permission = orig.permission;

	strcpy_s(name, orig.name);
	strcpy_s(units, orig.units);
	strcpy_s(format, orig.format);
	strcpy_s(description, orig.description);

	std::copy(orig.validValues.begin(), orig.validValues.end(), std::back_inserter(validValues));
}

LDSEntry& LDSEntry::operator=(const LDSEntry& rhs)
{
	LDSEntry temp(rhs);
	swap(temp);
	return *this;
}

LDSEntry::LDSEntry(LDSEntry&& orig) noexcept
{
	*this = std::move(orig);
}

LDSEntry& LDSEntry::operator=(LDSEntry&& rhs) noexcept
{
	if (this != &rhs)
	{
		key = rhs.key;
		length = rhs.length;
		permission = rhs.permission;

		std::move(rhs.name, rhs.name + MAX_DATA, name);
		std::move(rhs.units, rhs.units + MAX_DATA, units);
		std::move(rhs.format, rhs.format + MAX_DATA, format);
		std::move(rhs.description, rhs.description + MAX_DATA, description);

		std::move(rhs.validValues.begin(), rhs.validValues.end(), std::back_inserter(validValues));

		rhs.key = 0;
		rhs.length = 0;
		rhs.permission = 0;
	}
	return *this;
}

LDSEntry::~LDSEntry()
{

}

void LDSEntry::swap(LDSEntry& orig)
{
	std::swap(key, orig.key);
	std::swap(length, orig.length);
	std::swap(permission, orig.permission);

	std::swap(name, orig.name);
	std::swap(units, orig.units);
	std::swap(format, orig.format);
	std::swap(description, orig.description);

	std::swap(validValues, orig.validValues);
}

static int fetch_list_callback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<LDSEntry>* vec = (std::vector<LDSEntry>*) data;
	LDSEntry entry;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(azColName[i], "Key") == 0)
		{
			entry.key = atoi(argv[i]);
		}
		else if (strcmp(azColName[i], "Name") == 0)
		{
			strcpy_s(entry.name, argv[i]);
		}
		else if (strcmp(azColName[i], "Units") == 0)
		{
			strcpy_s(entry.units, argv[i]);
		}
		else if (strcmp(azColName[i], "Format") == 0)
		{
			strcpy_s(entry.format, argv[i]);
		}
		else if (strcmp(azColName[i], "Length") == 0)
		{
			entry.length = atoi(argv[i]);
		}
		else if (strcmp(azColName[i], "Description") == 0)
		{
			strcpy_s(entry.description, argv[i]);
		}
	}
	vec->push_back(entry);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Template member function definition

template<class T>
size_t LDSDatabase::fetch_list(T back_inserter)
{
	int rc = 0;
	char* zErrMsg;
	const char* cmdstr = "select Key, Name, Units, Format, Length, Description from UasLds;";
	std::vector<LDSEntry> res;

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_list_callback, (void*)&res, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}

	std::copy(res.begin(), res.end(), back_inserter);
	return res.size();
}

template<class T>
size_t LDSDatabase::fetch_security_list(T backInsertIt)
{
	size_t ret = fetch_security_elements(backInsertIt);
	return ret;
}

struct IsEqual
{
	int key_;
	bool operator() (const LDSEntry& entry) const
	{
		return entry.key == key_ ? true : false;
	}
};

static int fetch_security_elements_validvalues_callback(void* data, int argc, char** argv, char** azColName)
{
	std::multimap<int, ValidValue>* mapVv = (std::multimap<int, ValidValue>*) data;
	ValidValue vv;
	int key = 0;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(azColName[i], "DisplayName") == 0)
		{
			strcpy_s(vv.displayName, argv[i]);
		}
		else if (strcmp(azColName[i], "ValidValue") == 0)
		{
			strcpy_s(vv.value, argv[i]);
		}
		else if (strcmp(azColName[i], "CodingMethodId") == 0)
		{
			strcpy_s(vv.codingMethod, argv[i]);
		}
		else if (strcmp(azColName[i], "Key") == 0)
		{
			key = atoi(argv[i]);
		}
	}
	mapVv->insert(std::make_pair(key, vv));
	return 0;
}


template<class T>
size_t LDSDatabase::fetch_security_elements_validvalues(T first, T last)
{
	char* zErrMsg = 0;
	int rc = 0;

	std::multimap<int, ValidValue> mapVv;

	rc = sqlite3_exec(_pimpl->_db, IDS_QUERY_VALIDVALUES, fetch_security_elements_validvalues_callback, (void*)&mapVv, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}

	for (T it = first; it != last; ++it)
	{
		std::pair < std::multimap<int, ValidValue>::iterator, std::multimap<int, ValidValue>::iterator> ret;
		ret = mapVv.equal_range(it->key);
		for (std::multimap<int, ValidValue>::iterator vv = ret.first; vv != ret.second; ++vv)
		{
			it->validValues.push_back(vv->second);
		}
	}

	return mapVv.size();
}


template<class T>
size_t LDSDatabase::fetch_security_elements(T backInsertIt)
{
	int rc = 0;
	char* zErrMsg;
	const char* cmdstr = "select Key, Name, Units, Format, Length from Securitylds;";
	std::vector<LDSEntry> res;

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_list_callback, (void*)&res, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}
	std::copy(res.begin(), res.end(), backInsertIt);
	return res.size();
}

static int fetch_list_rights_callback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<LDSEntry>* vec = (std::vector<LDSEntry>*) data;
	LDSEntry entry;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(azColName[i], "KlvTag") == 0)
		{
			entry.key = atoi(argv[i]);
		}
		if (strcmp(azColName[i], "Name") == 0)
		{
			strcpy_s(entry.name, argv[i]);
		}
		else if (strcmp(azColName[i], "Units") == 0)
		{
			strcpy_s(entry.units, argv[i]);
		}
		else if (strcmp(azColName[i], "Format") == 0)
		{
			strcpy_s(entry.format, argv[i]);
		}
		else if (strcmp(azColName[i], "Length") == 0)
		{
			entry.length = atoi(argv[i]);
		}
		else if (strcmp(azColName[i], "CRUD") == 0)
		{
			entry.permission = (unsigned char)atoi(argv[i]);
		}
	}
	vec->push_back(entry);
	return 0;
}

template<class T> 
size_t LDSDatabase::fetch_list_rights(T backInsertIt, const char* countryCode)
{
	int rc = 0;
	char* zErrMsg;
	char cmdstr[BUFSIZ]{};
	std::vector<LDSEntry> res;

	sprintf_s(cmdstr, IDS_QUERY_RIGHTS, countryCode, countryCode);

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_list_rights_callback, (void*)&res, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}

	std::copy(res.begin(), res.end(), backInsertIt);
	return res.size();
}


template<class T> 
size_t LDSDatabase::fetch_security_list_rights(T backInsertIt, const char* countryCode)
{
	int rc = 0;
	char* zErrMsg;
	char cmdstr[BUFSIZ]{};
	std::vector<LDSEntry> res;

	sprintf_s(cmdstr, IDS_QUERY_SECURITY_RIGHTS, countryCode, countryCode);

	rc = sqlite3_exec(_pimpl->_db, cmdstr, fetch_list_rights_callback, (void*)&res, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}

	std::copy(res.begin(), res.end(), backInsertIt);
	return res.size();
}

//----------------------------------------------------------------
// Instantiate template member functions and export them from the DLL.
template size_t LDSDatabase::fetch_list<std::back_insert_iterator<std::vector<LDSEntry>>>(std::back_insert_iterator<std::vector<LDSEntry>>);
template size_t LDSDatabase::fetch_security_list<std::back_insert_iterator<std::vector<LDSEntry>>>(std::back_insert_iterator<std::vector<LDSEntry>>);
template size_t LDSDatabase::fetch_security_elements_validvalues<std::vector<LDSEntry>::iterator>(std::vector<LDSEntry>::iterator, std::vector<LDSEntry>::iterator);
template size_t LDSDatabase::fetch_security_elements<std::back_insert_iterator<std::vector<LDSEntry>> >(std::back_insert_iterator<std::vector<LDSEntry>>);
template size_t LDSDatabase::fetch_list_rights<std::back_insert_iterator<std::vector<LDSEntry>>>(std::back_insert_iterator<std::vector<LDSEntry>>, const char*);
template size_t LDSDatabase::fetch_security_list_rights<std::back_insert_iterator<std::vector<LDSEntry>>>(std::back_insert_iterator<std::vector<LDSEntry>>, const char*);
