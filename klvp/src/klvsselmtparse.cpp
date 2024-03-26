#include "klvelmt.h"
#include "klvsselmtimpl.h"
#include "decode.h"

// klvsslex generated on Thu Aug 15 09:15:01 2013

int lcss::KLVElement::parseSecuritySetElement(uint8_t* buf, int size)
{
	int p = 0;
	uint8_t key = buf[p++];

	switch (key)
	{
	case 1:
	{
		int len = buf[p++];
		if (len == 1 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSecurityClassification);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Security Classification."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 2:
	{
		int len = buf[p++];
		if (len == 1 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else
		{
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classifying Country and Releasing Instructions Country Coding Method."));
			for (size_t i = 0; i < len; i++)
			{
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 3:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassifyingCountry);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else
		{
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classifying Country."));
			for (size_t i = 0; i < len; i++)
			{
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 4:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSecuritySCISHIinformation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Security-SCI/SHI information."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 5:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCaveats);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Caveats."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 6:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVReleasingInstructions);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Releasing Instructions."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 7:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassifiedBy);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classified By."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 8:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVDerivedFrom);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Derived From."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 9:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassificationReason);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classification Reason."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 10:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVDeclassificationDate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Declassification Date."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 11:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassificationandMarkingSystem);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classification and Marking System."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 12:
	{
		int len = buf[p++];
		if (len == 1 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVObjectCountryCodingMethod);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Object Country Coding Method."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 13:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVObjectCountryCodes);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Object Country Codes."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 14:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassificationComments);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classification Comments."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 15:
	{
		int len = buf[p++];
		if (len == 32 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUMIDVideo);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing UMID Video."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 16:
	{
		int len = buf[p++];
		if (len == 32) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUMIDAudio);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing UMID Audio."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 17:
	{
		int len = buf[p++];
		if (len == 32) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUMIDData);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing UMID Data."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 18:
	{
		int len = buf[p++];
		if (len == 32) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUMIDSystem);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing UMID System."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 19:
	{
		int len = buf[p++];
		if (len == 1 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVStreamID);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Stream ID."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 20:
	{
		int len = buf[p++];
		if (len == 2 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTransportStreamID);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Transport Stream ID."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 21:
	{
		int len = buf[p++];
		if (len == 16 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVItemDesignator);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Item Designator."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 22:
	{
		int len = buf[p++];
		if (len == 2 || len == 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVVersion);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Version."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 23:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Classifying Country and Releasing Instructions Country Coding Method Version Date."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	case 24:
	{
		int numOfBytesRead = 0;
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVObjectCountryCodingMethodVersionDate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVParseError>(new lcss::KLVParseError(key, "Syntax error when parsing Object Country Coding Method Version Date."));
			for (size_t i = 0; i < len; i++) {
				if (i < size)
					pimpl_->push_back(buf[p++]);
			}
		}
	} break;
	default:
	{
		int len = buf[p++];
		pimpl_ = std::shared_ptr<lcss::KLVUnknownSecurity>(new lcss::KLVUnknownSecurity(key));
		for (size_t i = 0; i < len; i++)
			pimpl_->push_back(buf[p++]);
	}
	}
	return p;
}