#include "KLVPrintVisitor.h"

#include "TestKLVSecuritySetParser.h"

#include <cstdint>
#include <iomanip>
#include <iostream>
#ifdef WIN32
#include <WinSock2.h>
#endif

using namespace std;

namespace
{
	void printString(const char* classname, int key, const uint8_t* buf, uint16_t bufsize)
	{
		cout << "\t\t<" << classname << " key=\"" << key << "\">";
		for (int i = 0; i < bufsize; i++)
		{
			if (isprint(buf[i]))
				cout << (char)buf[i];
			else if (buf[i] != NULL)
				cout << hex << buf[i] << dec;
		}
		cout << "</" << classname << ">" << endl;
	}

	void printStringElement(const lcss::KLVElementImpl& klv)
	{
		uint8_t buf[128];
		memset(buf, 0, 128);
		klv.value(buf);
		printString(typeid(klv).name() + 12, klv.key(), buf, klv.length());
	}

	void printFloatElement(lcss::KLVElementImpl& klv, lcss::KLVDecodeVisitor& decoder)
	{
		klv.Accept(decoder);
		const char* classname = typeid(klv).name() + 12;
		cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << decoder.fValue << "</" << classname << ">" << endl;
	}

	void printIntElement(lcss::KLVElementImpl& klv, lcss::KLVDecodeVisitor& decoder)
	{
		klv.Accept(decoder);
		const char* classname = typeid(klv).name() + 12;
		cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << decoder.nValue << "</" << classname << ">" << endl;
	}

	void printNotImplemented(lcss::KLVElementImpl& klv)
	{
		const char* classname = typeid(klv).name() + 12;
		cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">Not Implmented</" << classname << ">" << endl;
	}

	int encodeBERLength(uint8_t* buffer, int len)
	{
		int bytesUsed = 0;
		if (len < 128)
		{
			uint8_t c = (uint8_t)len;
			*buffer = c;
			bytesUsed = 1;
		}
		else if (len > 127 && len < 256)
		{
			uint8_t c = 0x81;
			*buffer++ = c;
			uint8_t sz = (uint8_t)len;
			*buffer = sz;
			bytesUsed = 2;
		}
		else if (len > 255 && len < 65536)
		{
			uint8_t c = 0x82;
			*buffer++ = c;
			uint16_t sz = htons(len);
			uint8_t s[2];
			memcpy(s, (void*)&sz, 2);
			*buffer++ = s[0];
			*buffer = s[1];
			bytesUsed = 3;
		}
		return bytesUsed;
	}
}

KLVPrintVisitor::KLVPrintVisitor(const char* dbUri)
{
	cout.precision(6);
	cout << fixed;
}

void KLVPrintVisitor::Visit(lcss::KLVUnknown& klv)
{
	uint16_t key = (uint16_t)klv.key();
	uint8_t* val = new uint8_t[klv.length()];
	memset(val, 0, klv.length());
	klv.value(val);

	cout << "\t\t<KLVUnknown key=\"" << key << "\" length=\"" << klv.length() << "\">";
	for (int i = 0; i < klv.length(); i++)
	{
		cout << "0x" << setw(2) << setfill('0') << hex << (int)val[i] << " ";
	}
	cout << dec << "</KLVUnknown>" << endl;
	delete[] val;
}

void KLVPrintVisitor::Visit(lcss::KLVParseError& klv)
{
	uint16_t key = (uint16_t)klv.key();
	uint8_t* val = new uint8_t[klv.length()];
	memset(val, 0, klv.length());
	klv.value(val);

	cout << "\t\t<KLVParseError key=\"" << key << "\" length=\"" << klv.length() << "\" what=\"" << klv.what_.c_str() << "\">";
	for (int i = 0; i < klv.length(); i++)
	{
		cout << "0x" << setw(2) << setfill('0') << hex << (int)val[i] << " ";
	}
	cout << dec << "</KLVParseError>" << endl;
	delete[] val;
}

void KLVPrintVisitor::Visit(lcss::KLVChecksum& klv)
{
	uint8_t val[2];
	memset(val, 0, 2);
	klv.value(val);
	char crc[16];
	sprintf_s(crc, "%#4.2x %#4.2x", val[0], val[1]);

	const char* classname = typeid(klv).name() + 12;
	cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << crc << "</" << classname << ">" << endl;
}

void KLVPrintVisitor::Visit(lcss::KLVUNIXTimeStamp& klv)
{
	struct tm st;
	uint8_t value[8];
	klv.value(value);
	char timebuf[BUFSIZ];
	klv.Accept(_decoder);

	int usec = _decoder.tmValue % 1000000; // microseconds
	time_t time = (time_t)_decoder.tmValue / 1e6; // seconds

	gmtime_s(&st, &time);
	char szTime[BUFSIZ];
	strftime(szTime, BUFSIZ, "%A, %d-%b-%y %T", &st);
	_snprintf_s(timebuf, BUFSIZ, "%s.%06ld UTC", szTime, usec);
	const char* classname = typeid(klv).name() + 12;
	cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << timebuf << "</" << classname << ">" << endl;
}

void KLVPrintVisitor::Visit(lcss::KLVMissionID& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformTailNumber& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformHeadingAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformPitchAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformRollAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformTrueAirspeed& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformIndicatedAirspeed& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformDesignation& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVImageSourceSensor& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVImageCoordinateSystem& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorLatitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorLongitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorTrueAltitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorHorizontalFieldofView& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorVerticalFieldofView& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorRelativeAzimuthAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorRelativeElevationAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorRelativeRollAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSlantRange& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetWidth& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVFrameCenterLatitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVFrameCenterLongitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVFrameCenterElevation& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint1& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint1& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint2& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint2& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint3& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint3& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint4& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint4& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVIcingDetected& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVWindDirection& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVWindSpeed& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVStaticPressure& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVDensityAltitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOutsideAirTemperature& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetLocationLatitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetLocationLongitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetLocationElevation& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetTrackGateWidth& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetTrackGateHeight& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetErrorEstimateCE90& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetErrorEstimateLE90& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVGenericFlagData01& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSecurityLocalMetadataSet& klv)
{
	uint8_t ss[BUFSIZ]{};
	uint8_t value[BUFSIZ]{};
	klv.value(value);
	ss[0] = 0x30;

	const int bytesEncoded = encodeBERLength(ss + 1, klv.length());
	memcpy(ss + 1 + bytesEncoded, value, klv.length());

	TestKLVSecuritySetParser ssp;
	ssp.parse({ ss, gsl::narrow_cast<std::size_t>(klv.length() + bytesEncoded + 1) });
}

void KLVPrintVisitor::Visit(lcss::KLVDifferentialPressure& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformAngleofAttack& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformVerticalSpeed& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformSideslipAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAirfieldBarometicPressure& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAirfieldElevation& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVRelativeHumidity& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformGroundSpeed& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVGroundRange& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformFuelRemaining& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformCallSign& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVWeaponLoad& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVWeaponFired& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVLaserPRFCode& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorFieldofViewName& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformMagneticHeading& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVUASLDSVersionNumber& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetLocationCovarianceMatrix& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformLatitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformLongitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformAltitude& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformName& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformHeading& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVEventStartTimeUTC& klv)
{
	struct tm st;
	uint8_t value[8];
	klv.value(value);
	char timebuf[BUFSIZ];
	klv.Accept(_decoder);

	int usec = _decoder.tmValue % 1000000; // microseconds
	time_t time = (time_t)_decoder.tmValue / 1e6; // seconds

	gmtime_s(&st, &time);
	char szTime[BUFSIZ];
	strftime(szTime, BUFSIZ, "%A, %d-%b-%y %T", &st);
	_snprintf_s(timebuf, BUFSIZ, "%s.%06ld UTC", szTime, usec);
	const char* classname = typeid(klv).name() + 12;
	cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << timebuf << "</" << classname << ">" << endl;
}

void KLVPrintVisitor::Visit(lcss::KLVRVTLocalDataSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVVMTILocalDataSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorEllipsoidHeight& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeight& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOperationalMode& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVFrameCenterHeightAboveEllipsoid& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorNorthVelocity& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorEastVelocity& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVImageHorizonPixelPack& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLatitudePoint1Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLongitudePoint1Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLatitudePoint2Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLongitudePoint2Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLatitudePoint3Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLongitudePoint3Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLatitudePoint4Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCornerLongitudePoint4Full& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformPitchAngleFull& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformRollAngleFull& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformAngleofAttackFull& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformSideslipAngleFull& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVMIISCoreIdentifier& klv)
{
	uint8_t value[18];
	klv.value(value);
	char uuid[BUFSIZ];

	sprintf_s(uuid, "%02X%02X:%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7],
		value[8], value[9], value[10], value[11], value[12], value[13], value[14],
		value[15], value[16], value[17]);

	const char* classname = typeid(klv).name() + 12;
	cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << uuid << "</" << classname << ">" << endl;
}

void KLVPrintVisitor::Visit(lcss::KLVSARMotionImageryMetadata& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetWidthExtended& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVRangeImageLocalSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVGeoRegistrationLocalSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVCompositeImagingLocalSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVSegmentLocalSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVAmendLocalSet& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVSDCCFLP& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVDensityAltitudeExtended& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorEllipsoidHeightExtended& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeightExtended& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVStreamDesignator& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVOperationalBase& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVBroadcastSource& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVRangeToRecoveryLocation& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVTimeAirborne& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPropulsionUnitSpeed& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformCourseAngle& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVAltitudeAGL& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVRadarAltimeter& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVControlCommand& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVControlCommandVerificationList& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorAzimuthRate& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorElevationRate& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorRollRate& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOnboardMIStoragePercentFull& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVActiveWavelengthList& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVCountryCodes& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVNumberofNAVSATsinView& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPositioningMethodSource& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVPlatformStatus& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorControlMode& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVSensorFrameRatePack& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVWavelengthsList& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVTargetID& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVAirbaseLocations& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVTakeoffTime& klv)
{
	std::string strValue;
	uint8_t value[8];
	klv.value(value);
	char timebuf[26];
	__int64 lVal;
	memcpy(&lVal, value, 8);
	__time64_t time = ntohll(lVal);
	int n = time % 1000000;
	n = n / 1000; // milliseconds
	time = time / 1000000;

	errno_t err = _ctime64_s(timebuf, sizeof(timebuf), &time);
	if (err)
	{
		strValue = string("\"Error\"");
	}
	else
	{
		timebuf[24] = 0; //remove the carriage return
		strValue = string(timebuf);
		strValue += " (";
		char num[64];
		_itoa_s(n, num, 10);
		strValue += num;
		strValue += " ms)";
	}
	const char* classname = typeid(klv).name() + 12;
	cout << "\t\t<" << classname << " key=\"" << (int)klv.key() << "\">" << strValue.c_str() << "</" << classname << ">" << endl;
}

void KLVPrintVisitor::Visit(lcss::KLVTransmissionFrequency& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVOnboardMIStorageCapacity& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVZoomPercentage& klv)
{
	printFloatElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCommunicationsMethod& klv)
{
	printStringElement(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVLeapSeconds& klv)
{
	printIntElement(klv, _decoder);
}

void KLVPrintVisitor::Visit(lcss::KLVCorrectionOffset& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVPayloadList& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVActivePayloads& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVWeaponsStores& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::KLVWaypointList& klv)
{
	printNotImplemented(klv);
}

void KLVPrintVisitor::Visit(lcss::UniversalMetadataElement& klv)
{
	uint8_t key[16];
	klv.key(key);
	uint8_t* val = new uint8_t[klv.length()];
	memset(val, 0, klv.length());
	klv.value(val);

	cout << "\t\t<UniversalSetElement key=\"";
	for (int i = 0; i < 16; i++)
	{
		cout << "0x" << setw(2) << setfill('0') << hex << (int)key[i];
		if (i < 15)
			cout << " ";
	}
	cout << "\">";
	for (int i = 0; i < klv.length(); i++)
	{
		cout << "0x" << setw(2) << setfill('0') << hex << (int)val[i];
		if (i < klv.length() - 1)
			cout << " ";
	}
	cout << dec << "</UniversalSetElement>" << endl;
	delete[] val;
}
