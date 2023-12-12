#include "decode.h"

#include "FpParser.h"

#include <cstdint>
#include <string.h>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>

#define _WS2_32_WINSOCK_SWAP_LONGLONG(l)            \
            ( ( ((l) >> 56) & 0x00000000000000FFLL ) |       \
              ( ((l) >> 40) & 0x000000000000FF00LL ) |       \
              ( ((l) >> 24) & 0x0000000000FF0000LL ) |       \
              ( ((l) >>  8) & 0x00000000FF000000LL ) |       \
              ( ((l) <<  8) & 0x000000FF00000000LL ) |       \
              ( ((l) << 24) & 0x0000FF0000000000LL ) |       \
              ( ((l) << 40) & 0x00FF000000000000LL ) |       \
              ( ((l) << 56) & 0xFF00000000000000LL ) )

uint64_t ntohll ( uint64_t Value ) 
{ 
    const uint64_t Retval = _WS2_32_WINSOCK_SWAP_LONGLONG (Value);
    return Retval;
}
#endif

namespace lcss
{
	KLVDecodeVisitor::KLVDecodeVisitor()
		: tmValue(0)
		, fValue(0.0)
		, nValue(0)
		, frameCenterLat(0.0)
		, frameCenterLon(0.0)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVUnknown& klv)
	{
	}

	void KLVDecodeVisitor::Visit(lcss::KLVParseError& klv)
	{
	}

	void KLVDecodeVisitor::Visit(lcss::KLVChecksum& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		nValue = (int) nVal;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVUNIXTimeStamp& klv)
	{
		int64_t lVal;
		memcpy(&lVal, klv.value(), 8);
#ifdef WIN32
		tmValue = ntohll(lVal);
#else
		tmValue = lVal;
#endif
	}

	void KLVDecodeVisitor::Visit(lcss::KLVMissionID& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformTailNumber& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformHeadingAngle& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 360.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformPitchAngle& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = 40.0 / 0xFFFE * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformRollAngle& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = 100.0 / 0xFFFE * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformTrueAirspeed& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformIndicatedAirspeed& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformDesignation& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVImageSourceSensor& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVImageCoordinateSystem& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorLatitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		if (klv.key() == 0x17)
			frameCenterLat = UDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorLongitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		if (klv.key() == 0x18)
			frameCenterLon = UDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorTrueAltitude& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorHorizontalFieldofView& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 180.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorVerticalFieldofView& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 180.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorRelativeAzimuthAngle& klv)
	{
		uint32_t nVal;
		memcpy(&nVal, klv.value(), 4);
		uint32_t LDS = (uint32_t)ntohl(nVal);
		fValue = 360.0 / 0xFFFFFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorRelativeElevationAngle& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		fValue = 360.0 / 0xFFFFFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorRelativeRollAngle& klv)
	{
		uint32_t nVal;
		memcpy(&nVal, klv.value(), 4);
		uint32_t LDS = (uint32_t)ntohl(nVal);
		fValue = 360.0 / 0xFFFFFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSlantRange& klv)
	{
		uint32_t nVal;
		memcpy(&nVal, klv.value(), 4);
		uint32_t LDS = ntohl(nVal);
		fValue = 5000000.0 / 0xFFFFFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetWidth& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 10000.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVFrameCenterLatitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		frameCenterLat = UDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVFrameCenterLongitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		frameCenterLon = UDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVFrameCenterElevation& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint1& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLat;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint1& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLon;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint2& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLat;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint2& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLon;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint3& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLat;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint3& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLon;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint4& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLat;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint4& klv)
	{
		short nVal;
		memcpy(&nVal, klv.value(), 2);
		short LDS = ntohs(nVal);
		fValue = (0.15 / 0xFFFE * LDS) + frameCenterLon;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVIcingDetected& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVWindDirection& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 360.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVWindSpeed& klv)
	{
		uint16_t LDS = (uint16_t)*klv.value();
		fValue = (100.0 / 0xFF) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVStaticPressure& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (5000.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVDensityAltitude& klv)
	{
		unsigned short LDS{ 0 };
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOutsideAirTemperature& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetLocationLatitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetLocationLongitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetLocationElevation& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetTrackGateWidth& klv)
	{
		fValue = 2.0 * *klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetTrackGateHeight& klv)
	{
		fValue = 2.0 * *klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetErrorEstimateCE90& klv)
	{
		uint16_t LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		fValue = (4095.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetErrorEstimateLE90& klv)
	{
		uint16_t LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		fValue = (4095.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVGenericFlagData01& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSecurityLocalMetadataSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVDifferentialPressure& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (5000.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformAngleofAttack& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (40.0 / 65534.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformVerticalSpeed& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (360.0 / 65534.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformSideslipAngle& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (40.0 / 65534.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAirfieldBarometicPressure& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (5000.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAirfieldElevation& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVRelativeHumidity& klv)
	{
		uint16_t LDS = (uint16_t)*klv.value();
		fValue = (100 / 0xFF) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformGroundSpeed& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVGroundRange& klv)
	{
		uint32_t nVal;
		memcpy(&nVal, klv.value(), 4);
		uint32_t LDS = ntohl(nVal);
		fValue = 5000000.0 / 0xFFFFFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformFuelRemaining& klv)
	{
		short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (10000.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformCallSign& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVWeaponLoad& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		nValue = (int) ntohs(nVal);
	}

	void KLVDecodeVisitor::Visit(lcss::KLVWeaponFired& klv)
	{
		nValue = (int) *klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVLaserPRFCode& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		nValue = (int)ntohs(nVal);
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorFieldofViewName& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformMagneticHeading& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = 360.0 / 0xFFFF * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVUASLDSVersionNumber& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetLocationCovarianceMatrix& klv)
	{
		// Deprecated
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformLatitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformLongitude& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformAltitude& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformName& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformHeading& klv)
	{
		unsigned short LDS = 0;
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = (360.0 / 65535.0) * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVEventStartTimeUTC& klv)
	{
		int64_t lVal;
		memcpy(&lVal, klv.value(), 8);
		tmValue = ntohll(lVal);
	}

	void KLVDecodeVisitor::Visit(lcss::KLVRVTLocalDataSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVVMTILocalDataSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorEllipsoidHeight& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeight& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOperationalMode& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVFrameCenterHeightAboveEllipsoid& klv)
	{
		uint16_t nVal;
		memcpy(&nVal, klv.value(), 2);
		uint16_t LDS = ntohs(nVal);
		fValue = (19900.0 / 0xFFFF * LDS) - 900;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorNorthVelocity& klv)
	{
		short LDS{ 0 };
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = 654.0 / 65534.0 * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorEastVelocity& klv)
	{
		short LDS{ 0 };
		memcpy(&LDS, klv.value(), 2);
		LDS = ntohs(LDS);
		fValue = 654.0 / 65534.0 * LDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVImageHorizonPixelPack& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLatitudePoint1Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLongitudePoint1Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLatitudePoint2Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLongitudePoint2Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLatitudePoint3Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLongitudePoint3Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLatitudePoint4Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCornerLongitudePoint4Full& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformPitchAngleFull& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformRollAngleFull& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformAngleofAttackFull& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 180.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformSideslipAngleFull& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		int LDS = ntohl(nVal);
		double UDS = 360.0 / 0xFFFFFFFE * LDS;
		fValue = UDS;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVMIISCoreIdentifier& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVSARMotionImageryMetadata& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetWidthExtended& klv)
	{
		FpParser fpp(0.0, 1500000.0, klv.length());
		fValue = fpp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVRangeImageLocalSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVGeoRegistrationLocalSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVCompositeImagingLocalSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVSegmentLocalSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVAmendLocalSet& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVSDCCFLP& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVDensityAltitudeExtended& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorEllipsoidHeightExtended& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeightExtended& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVStreamDesignator& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOperationalBase& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVBroadcastSource& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVRangeToRecoveryLocation& klv)
	{
		FpParser ffp(0.0, 21000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTimeAirborne& klv)
	{
		unsigned int val;
		memcpy(&val, klv.value(), 4);
		val = ntohl(val);
		nValue = val;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPropulsionUnitSpeed& klv)
	{
		unsigned int val;
		memcpy(&val, klv.value(), 4);
		val = ntohl(val);
		nValue = val;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformCourseAngle& klv)
	{
		FpParser ffp(0.0, 360.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAltitudeAGL& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVRadarAltimeter& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVControlCommand& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVControlCommandVerificationList& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorAzimuthRate& klv)
	{
		FpParser ffp(-1000.0, 1000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorElevationRate& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorRollRate& klv)
	{
		FpParser ffp(-900.0, 40000.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOnboardMIStoragePercentFull& klv)
	{
		FpParser ffp(0.0, 100.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVActiveWavelengthList& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVCountryCodes& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVNumberofNAVSATsinView& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPositioningMethodSource& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPlatformStatus& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorControlMode& klv)
	{
		nValue = (int)*klv.value();
	}

	void KLVDecodeVisitor::Visit(lcss::KLVSensorFrameRatePack& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVWavelengthsList& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVTargetID& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVAirbaseLocations& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVTakeoffTime& klv)
	{
		int64_t lVal;
		memcpy(&lVal, klv.value(), 8);
		int64_t time = ntohll(lVal);
		tmValue = time / 1000000;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVTransmissionFrequency& klv)
	{
		FpParser ffp(1.0, 99999.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVOnboardMIStorageCapacity& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		nValue = ntohl(nVal);
	}

	void KLVDecodeVisitor::Visit(lcss::KLVZoomPercentage& klv)
	{
		FpParser ffp(0.0, 100.0, klv.length());
		fValue = ffp.decode(klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCommunicationsMethod& klv)
	{
		strValue = std::string((char*)klv.value(), klv.length());
	}

	void KLVDecodeVisitor::Visit(lcss::KLVLeapSeconds& klv)
	{
		int nVal;
		memcpy(&nVal, klv.value(), 4);
		nValue = ntohl(nVal);
	}

	void KLVDecodeVisitor::Visit(lcss::KLVCorrectionOffset& klv)
	{
		int64_t lVal;
		memcpy(&lVal, klv.value(), 8);
		int64_t time = ntohll(lVal);
		tmValue = time / 1000000;
	}

	void KLVDecodeVisitor::Visit(lcss::KLVPayloadList& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVActivePayloads& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVWeaponsStores& klv)
	{

	}

	void KLVDecodeVisitor::Visit(lcss::KLVWaypointList& klv)
	{

	}


	int decodeBERLength(int* numBytesRead, const uint8_t* buffer, int size)
	{
		int i = 0;
		int len = 0;
		if (buffer[i] < 128) {
			*numBytesRead = 1;
			return buffer[i];
		}
		else {
			switch (buffer[i] ^ 0x80)
			{
			case 1:
				*numBytesRead = 2;
				return buffer[++i];
				break;
			case 2:
				*numBytesRead = 3;
				memcpy(&len, buffer + 1, 2);
				return ntohs(len);
				break;
			case 3:
				*numBytesRead = 4;
				memcpy(&len, buffer + 1, 3);
				len = ntohl(len);
				return len >> 5;
				break;
			case 4:
				*numBytesRead = 5;
				memcpy(&len, buffer + 1, 4);
				return ntohl(len);
				break;
			}
		}
		return 0;
	}

	int decodeKey(int* numBytesRead, const uint8_t* buffer, int size)
	{
		int i = 0;
		int decKey = 0;
		if (buffer[i] < 128) {
			*numBytesRead = 1;
			return buffer[i];
		}
		else 
		{
			*numBytesRead = 2;
			uint8_t b1 = buffer[i++] & 0x7F;
			uint8_t b2 = buffer[i];

			if (b1 & 0x01)
				decKey = 128 + b2;
		}
		return decKey;
	}

} // namespace lcss