#include "KLVSecuritySetPrintVisitor.h"

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string.h>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#define sprintf_s sprintf
#endif

// klvsslex generated on Tue Aug 06 10:36:49 2013

using namespace std;

void printString(const char* classname, int key, const uint8_t* buf, uint16_t bufsize)
{
	cout <<"\t\t\t<" << classname << " key=\"" << key << "\">";
	for(int i = 0; i < bufsize; i++)
	{
		if(isprint(buf[i]))
			cout << (char) buf[i];
		else
			cout << hex << buf[i] << dec;
	}
	cout << "</" << classname << ">" << endl;
}

void printNotImplemented(int key)
{
	cout << "\t\t\t<NotImplemented key=\"" << key << "\"/> " << endl;
}

KLVSecuritySetPrintVisitor::KLVSecuritySetPrintVisitor() {}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVUnknownSecurity& klv)
{
	uint16_t key = (uint16_t) klv.key();
    uint8_t* val = new uint8_t[klv.length()];
    memset(val,0,klv.length());
    klv.value(val);

    cout << "\t\t\t<KLVUnknownSecurity key=\"" << key << "\" length=\"" << klv.length() << "\">";
    for(int i = 0; i < klv.length(); i++)
    {
        cout << "0x" << setw(2) << setfill('0') << hex << (int) val[i] << " ";
    }
    cout << dec << "</KLVUnknownSecurity>" << endl;
    delete [] val;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVParseError& klv)
{
	uint16_t key = (uint16_t) klv.key();
    uint8_t* val = new uint8_t[klv.length()];
    memset(val,0,klv.length());
    klv.value(val);

    cout << "\t\t\t<KLVParseError key=\"" << key << "\" length=\"" << klv.length() << "\" what=\""<< klv.what_.c_str() << "\">";
    for(int i = 0; i < klv.length(); i++)
    {
        cout << "0x" << setw(2) << setfill('0') << hex << (int) val[i] << " ";
    }
    cout << dec << "</KLVParseError>" << endl;
    delete [] val;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVObjectCountryCodingMethodVersionDate& klv)
{
	uint8_t buf[10];
	memset(buf,0,10);
	klv.value(buf);
	printString("KLVObjectCountryCodingMethodVersionDate",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVSecurityClassification& klv)
{
	uint8_t value;
	klv.value(&value);
	cout << "\t\t\t<KLVSecurityClassification key=\"" << (int) klv.key() << "\">" << (int) value << "</KLVSecurityClassification>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod& klv)
{
	uint8_t value;
	klv.value(&value);
	cout << "\t\t\t<KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod key=\"" << (int) klv.key() << "\">" << (int) value << "</KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassifyingCountry& klv)
{
	uint8_t buf[128];
	memset(buf,0,128);
	klv.value(buf);
	printString("KLVClassifyingCountry",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVSecuritySCISHIinformation& klv)
{
	uint8_t buf[40];
	memset(buf,0,40);
	klv.value(buf);
	printString("KLVSecuritySCISHIinformation",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVCaveats& klv)
{
	uint8_t buf[32];
	memset(buf,0,32);
	klv.value(buf);
	printString("KLVCaveats",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVReleasingInstructions& klv)
{
	uint8_t buf[128];
	memset(buf,0,128);
	klv.value(buf);
	printString("KLVReleasingInstructions",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassifiedBy& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVDerivedFrom& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassificationReason& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVDeclassificationDate& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassificationandMarkingSystem& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVObjectCountryCodingMethod& klv)
{
	uint8_t value;
	klv.value(&value);
	cout << "\t\t\t<KLVObjectCountryCodingMethod key=\"" << (int) klv.key() << "\">" << (int) value << "</KLVObjectCountryCodingMethod>" << endl;
}

/// <summary>
/// Visits the specified KLV Security Element of type Object Country Codes, key = 13.
/// The string are UTF-16 encoded, so when displaying to output convert to UTF-8.
/// </summary>
/// <param name="klv">KLV Security Element.</param>
void KLVSecuritySetPrintVisitor::Visit(lcss::KLVObjectCountryCodes& klv)
{
	uint8_t buf[40];
	memset(buf,0,40);
	klv.value(buf);
	cout << "\t\t\t<KLVObjectCountryCodes key=\"13\">";
	for (int i = 0; i < klv.length(); i++)
	{
		if (isprint(buf[i]))
			cout << (char)buf[i];
	}
	cout << "</KLVObjectCountryCodes>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassificationComments& klv)
{
	uint8_t buf[40];
	memset(buf,0,40);
	klv.value(buf);
	printString("KLVClassificationComments",klv.key(),buf,klv.length());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVUMIDVideo& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVUMIDAudio& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVUMIDData& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVUMIDSystem& klv)
{
	printNotImplemented(klv.key());
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVStreamID& klv)
{
	uint8_t value;
	klv.value(&value);
	cout << "\t\t\t<KLVStreamID key=\"" << (int) klv.key() << "\">" << (int)value << "</KLVStreamID>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVTransportStreamID& klv)
{
	uint8_t value[2];
	klv.value(value);
	uint16_t val;
	memcpy(&val,value,2);
	uint16_t nValue = ntohs(val);
	cout << "\t\t\t<KLVTransportStreamID key=\"" << (int) klv.key() << "\">" << nValue << "</KLVTransportStreamID>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVItemDesignator& klv)
{
	uint8_t value[16];
	klv.value(value);
	cout << "\t\t\t<KLVItemDesignator key=\"" << (int) klv.key() << "\">";

	for(int i = 0; i < 16; i++)
	{
		char hexc[8];
		if(value[i]>0)
			sprintf_s(hexc,"%#4.2x",value[i]);
		else
			sprintf_s(hexc,"0x00");
		cout << hexc << " ";
	}
	cout << "</KLVItemDesignator>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVVersion& klv)
{
	uint8_t value[2];
	klv.value(value);
	uint16_t val;
	memcpy(&val,value,2);
	uint16_t nValue = ntohs(val);
	//uint16_t nValue = val;
	cout << "\t\t\t<KLVVersion key=\"" << (int) klv.key() << "\">" << nValue << "</KLVVersion>" << endl;
}

void KLVSecuritySetPrintVisitor::Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate& klv)
{
	uint8_t buf[10];
	memset(buf,0,10);
	klv.value(buf);
	printString("KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate",klv.key(),buf,klv.length());
}

