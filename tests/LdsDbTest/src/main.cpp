// LDS Database test

#include <ldsdb/ldsdb.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

#define LEN 3

int main(int argc, char *argv[])
{
	using namespace std;

	try
	{
		LDSDatabase ldsdb;

		bool ret = ldsdb.connect(argv[1]);

		if (!ret)
		{
			cerr << "fail to open database " << argv[1] << endl;
			return -1;
		}

		LDSEntry entry;
		entry.key = 1;

		ldsdb.fetch(&entry);

		if (strcmp(entry.name, "Checksum") == 0 &&
			strcmp(entry.description, "Checksum used to detect errors within a UAS Datalink LS packet") == 0 &&
			strcmp(entry.format, "uint16") == 0 &&
			strcmp(entry.units, "Binary") == 0 &&
			strcmp(entry.symbol, "checksum_16") == 0 &&
			entry.length == 2 &&
			entry.key == 1)
		{
			cout << "fetch() passed" << endl;
		}
		else
		{
			cout << "fetch() failed" << endl;
			return -1;
		}

		memset(&entry, 0, sizeof(LDSEntry));
		entry.key = 1;

		ldsdb.fetch_security(&entry);

		if (strcmp(entry.name, "Security Classification") == 0 &&
			strcmp(entry.format, "uint8") == 0 &&
			strcmp(entry.units, "Enumeration") == 0 &&
			entry.length == 1 &&
			entry.key == 1)
		{
			cout << "fetch_security() passed" << endl;
		}
		else
		{
			cout << "fetch() failed" << endl;
			return -1;
		}

		std::vector<LDSEntry> entries;
		size_t count = ldsdb.fetch_list(std::back_inserter(entries));

		if (count == 141)
		{
			cout << "fetch_list() passed" << endl;
		}
		else
		{
			cout << "fetch_list() failed" << endl;
			return -1;
		}

		entries.clear();
		count = ldsdb.fetch_security_list(std::back_inserter(entries));

		if (count == 24)
		{
			cout << "fetch_security_list() passed" << endl;
		}
		else
		{
			cout << "fetch_security_list() failed" << endl;
			return -1;
		}

		count = ldsdb.fetch_security_elements_validvalues(entries.begin(), entries.end());

		if (count == 37)
		{
			cout << "fetch_security_elements_validvalues() passed" << endl;
		}
		else
		{
			cout << "fetch_security_elements_validvalues() failed" << endl;
			return -1;
		}

		entries.clear();
		count = ldsdb.fetch_list_rights(std::back_inserter(entries), "CAN");

		if (count == 18)
		{
			cout << "fetch_list_rights() passed" << endl;
		}
		else
		{
			cout << "fetch_list_rights() failed" << endl;
			return -1;
		}

		entries.clear();
		count = ldsdb.fetch_security_list_rights(std::back_inserter(entries), "CAN");

		if (count == 22)
		{
			cout << "fetch_security_list_rights() passed" << endl;
		}
		else
		{
			cout << "fetch_security_list_rights() failed" << endl;
			return -1;
		}

		ldsdb.disconnect();
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what();
		return -1;
	}

	return 0;
}