#include "TestKLVSecuritySetParser.h"

#include "klvelmt.h"
#include "klvelmtimpl.h"

#include <iostream>

using namespace std;


TestKLVSecuritySetParser::TestKLVSecuritySetParser(void)
{
}


TestKLVSecuritySetParser::~TestKLVSecuritySetParser(void)
{
}

void TestKLVSecuritySetParser::onBeginSet(int len, lcss::KLVParser::TYPE type)
{
	lcss::KLVParser::onBeginSet(len, type);
	std::cout << "\t\t<LDS_Security_Set length=\"" << len  << "\">" << endl;
}

void TestKLVSecuritySetParser::onEndSet()
{
	lcss::KLVParser::onEndSet();
	std::cout << "\t\t</LDS_Security_Set>" << std::endl;
}

void TestKLVSecuritySetParser::onElement( lcss::KLVElement& klv)
{
	lcss::KLVParser::onElement(klv);
	klv.Accept(printVisitor_);
}

void TestKLVSecuritySetParser::onError(const char* errmsg, int pos)
{
	lcss::KLVParser::onError(errmsg,pos);
	std::cout <<"\t\t<ERROR msg=\"" << errmsg << "\" pos=\"" << pos << "\"/>" << std::endl;
}