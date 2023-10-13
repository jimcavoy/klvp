#include "TestKLVParser.h"

#include "klvelmt.h"
#include "klvelmtimpl.h"

#include <iostream>

using namespace std;


TestKLVParser::TestKLVParser(KLVPrintVisitor& printer)
	: count_(0)
	, type_(lcss::TYPE::LOCAL_SET)
	, printVisitor_(printer)
{
	//Validate Checksum
	validateChecksum(true);
}


TestKLVParser::~TestKLVParser(void)
{
}

void TestKLVParser::onBeginSet(int len, lcss::TYPE type)
{
	lcss::KLVParser::onBeginSet(len,type);
	type_ = type;

	switch (type_)
	{
	case lcss::TYPE::LOCAL_SET:
		std::cout << "\t<Local_Set length=\"" << len << "\" count=\"" << count_++ << "\">" << endl;
		break;
	case lcss::TYPE::UNIVERSAL_SET:
		std::cout << "\t<Universal_Set length=\"" << len << "\" count=\"" << count_++ << "\">" << endl;
		break;
	case lcss::TYPE::SECURITY_UNIVERSAL_SET:
		std::cout << "\t<Security_Universal_Set length=\"" << len << "\" count=\"" << count_++ << "\">" << endl;
		break;
	case lcss::TYPE::UNIVERSAL_ELEMENT:
		std::cout << "\t<Universal_Element length=\"" << len << "\" count=\"" << count_++ << "\">" << endl;
		break;
	}
	
}

void TestKLVParser::onEndSet()
{
	lcss::KLVParser::onEndSet();

	switch (type_)
	{
	case lcss::TYPE::LOCAL_SET: std::cout << "\t</Local_Set>" << std::endl; break;
	case lcss::TYPE::UNIVERSAL_SET: std::cout << "\t</Universal_Set>" << std::endl; break;
	case lcss::TYPE::SECURITY_UNIVERSAL_SET: std::cout << "\t</Security_Universal_Set>" << std::endl; break;
	case lcss::TYPE::UNIVERSAL_ELEMENT: std::cout << "\t</Universal_Element>" << std::endl; break;
	}
	
}

void TestKLVParser::onElement( lcss::KLVElement& klv)
{
	lcss::KLVParser::onElement(klv);
	std::cout.precision(6);
	klv.Accept(printVisitor_);
}

void TestKLVParser::onError(const char* errmsg, int pos)
{
	lcss::KLVParser::onError(errmsg,pos);
	std::cout <<"\t\t<ERROR msg=\"" << errmsg << "\" pos=\"" << pos << "\"/>" << std::endl;
}