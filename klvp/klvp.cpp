// klvp.cpp : Defines the entry point for the console application.
//

#include "klvp.h"

#include "TestKLVParser.h"
#include "KLVPrintVisitor.h"
#include <conio.h>
#include <fstream>

using namespace std;

const int N = 188*49;

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cerr << "usage: klvp infile databaseUrl" << endl;
		return -1;
	}

	ifstream ifile;
	ifile.open(argv[1],std::ios::in|std::ios::binary);
	if(!ifile.is_open())
	{
		printf("Error: Fail to open file %s", argv[1]);
		return -1;
	}

	printf("<KLV file=\"%s\">\n",argv[1]);


	KLVPrintVisitor pv(argv[2]);
	TestKLVParser p(pv);
	try
	{
		uint8_t memblock[N]{};
		while(ifile.good())
		{
			ifile.read((char*)memblock,N);
			p.parse({ memblock, gsl::narrow_cast<std::size_t>(ifile.gcount()) });
		}
	}
	catch(...)
	{
		cerr << "Unknown exception thrown\n";
	}

	cout << "</KLV>" << endl;

	cerr << "KLV count = " << p.count() << endl;
	//cerr << endl << "Enter any key to exit" << endl;
	//_getch();
	return 0;
}

