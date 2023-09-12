#include "encode.h"

#include "FpParser.h"

#include <Rpc.h>

// klvlex generated on Thu Apr 02 10:25:01 2015

#define U2LFP(a)   (((unsigned long long) \
                       ((a).tv_sec) * 1000000) + \
                       (unsigned long long) \
                       (a).tv_usec)

namespace
{
	void encodeString(lcss::KLVElementImpl& klv, std::string value)
	{
		klv.setValue((BYTE*)value.c_str(), (int)value.size());
	}

	int char2int(char input)
	{
		if (input >= '0' && input <= '9')
			return input - '0';
		if (input > 'A' && input <= 'F')
			return input - 'A' + 10;
		if (input > 'a' && input <= 'f')
			return input - 'a' + 10;
		return 0;
	}

}

namespace lcss
{

	KLVEncodeVisitor::KLVEncodeVisitor()
		: timestamp { 0, 0}
		, dblValue(0.0)
		, nValue(0)
		, frameCenterLatLon(0.0)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUnknown& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVParseError& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVChecksum& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVUNIXTimeStamp& klv)
	{
		time_t ltime = U2LFP(timestamp);
		time_t ntTime = htonll(ltime);
		memcpy(value, &ntTime, 8);
		klv.setValue(value, 8);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVMissionID& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformTailNumber& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformHeadingAngle& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 360.0) * UDS;
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformPitchAngle& klv)
	{
		double UDS = dblValue;
		short LDS = (short)0x8000;
		if (UDS >= -20.0 && UDS <= 20.0)
		{
			LDS = (UINT16)(0xFFFE / 40.0) * UDS;
		}
		short nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformRollAngle& klv)
	{
		double UDS = dblValue;
		short LDS = (short)0x8000;
		if (UDS >= -50.0 && UDS <= 50.0)
		{
			LDS = (UINT16)(0xFFFE / 100) * UDS;
		}
		short nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformTrueAirspeed& klv)
	{
		unsigned char ms = nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformIndicatedAirspeed& klv)
	{
		unsigned char ms = nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformDesignation& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVImageSourceSensor& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVImageCoordinateSystem& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorLatitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorLongitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorTrueAltitude& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorHorizontalFieldofView& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 180.0 * UDS);
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorVerticalFieldofView& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 180.0 * UDS);
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorRelativeAzimuthAngle& klv)
	{
		double SREA = dblValue;
		UINT32 LDS = (UINT32)(0xFFFFFFFF / 360.0 * SREA);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorRelativeElevationAngle& klv)
	{
		double SREA = dblValue;
		int LDS = 0x80000000;

		if (SREA >= -180.0 && SREA <= 180.0)
		{
			LDS = (UINT32)(0xFFFFFFFF / 360.0 * SREA);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorRelativeRollAngle& klv)
	{
		double SREA = dblValue;
		UINT32 LDS = (UINT32)(0xFFFFFFFF / 360.0 * SREA);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSlantRange& klv)
	{
		double UDS = dblValue;

		UINT32 LDS = (int)(0xFFFFFFFF / 5000000.0 * UDS);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetWidth& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 10000.0 * UDS);

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVFrameCenterLatitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVFrameCenterLongitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVFrameCenterElevation& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	static void SetLatLonOffset(lcss::KLVElementImpl& klv, double dblValue, double frameCenterLatLon)
	{
		double UDS = dblValue;
		short LDS = (short)0x8000;
		BYTE value[8];

		// Some client code will already determine the corner point is already off-earth
		// by setting the value 0x8000
		if (UDS != 0x8000)
		{
			double t1 = (UDS - frameCenterLatLon);
			if (t1 >= -0.075 && t1 <= 0.075)
			{
				double t2 = (0xFFFE / 0.15);
				double t3 = t2 * t1;
				LDS = (short)t3;
			}
		}

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}


	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint1& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint1& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint2& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint2& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint3& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint3& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLatitudePoint4& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOffsetCornerLongitudePoint4& klv)
	{
		SetLatLonOffset(klv, dblValue, frameCenterLatLon);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVIcingDetected& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVWindDirection& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 360 * UDS);
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVWindSpeed& klv)
	{
		BYTE LDS = (BYTE)(0xFF / 100 * dblValue);
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVStaticPressure& klv)
	{
		UINT16 LDS = (UINT16)(0xFFFF / 5000.0 * dblValue);
		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVDensityAltitude& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOutsideAirTemperature& klv)
	{
		BYTE LDS = (BYTE)(nValue);
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetLocationLatitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetLocationLongitude& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetLocationElevation& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetTrackGateWidth& klv)
	{
		BYTE LDS = (BYTE)floor(nValue / 2);
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetTrackGateHeight& klv)
	{
		BYTE LDS = (BYTE)floor(nValue / 2);
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetErrorEstimateCE90& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 4095.0 * UDS);

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetErrorEstimateLE90& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 4095.0 * UDS);

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVGenericFlagData01& klv)
	{
		BYTE ms = nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSecurityLocalMetadataSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVDifferentialPressure& klv)
	{
		UINT16 LDS = (UINT16)(0xFFFF / 5000.0 * dblValue);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformAngleofAttack& klv)
	{
		short LDS = (short)0x8000;

		if (dblValue >= -20.0 && dblValue <= 20.0)
		{
			LDS = (short)(0xFFFE / 40.0 * dblValue);
		}

		LDS = ntohs(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformVerticalSpeed& klv)
	{
		short LDS = (short)0x8000;

		if (dblValue >= -180.0 && dblValue <= 180.0)
		{
			LDS = (short)(0xFFFE / 360.0 * dblValue);
		}

		LDS = ntohs(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformSideslipAngle& klv)
	{
		short LDS = (short)0x8000;

		if (dblValue >= -20.0 && dblValue <= 20.0)
		{
			LDS = (short)(0xFFFE / 40.0 * dblValue);
		}

		LDS = ntohs(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAirfieldBarometicPressure& klv)
	{
		UINT16 LDS = (UINT16)(0xFFFF / 5000.0 * dblValue);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAirfieldElevation& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVRelativeHumidity& klv)
	{
		BYTE LDS = (BYTE)(0xFF / 100 * dblValue);
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformGroundSpeed& klv)
	{
		BYTE ms = nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVGroundRange& klv)
	{
		double UDS = dblValue;

		UINT32 LDS = (int)(0xFFFFFFFF / 5000000.0 * UDS);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformFuelRemaining& klv)
	{
		UINT16 LDS = (UINT)(0xFFFF / 10000 * dblValue);
		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformCallSign& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVWeaponLoad& klv)
	{
		UINT16 LDS = (UINT16)nValue;
		LDS = ntohs(nValue);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVWeaponFired& klv)
	{
		BYTE ms = nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVLaserPRFCode& klv)
	{
		UINT16 LDS = (UINT16)nValue;
		LDS = ntohs(nValue);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorFieldofViewName& klv)
	{
		BYTE ms = (BYTE) nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformMagneticHeading& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 360.0 * UDS);
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUASLDSVersionNumber& klv)
	{
		BYTE ms = (BYTE)nValue;
		klv.setValue(&ms, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetLocationCovarianceMatrix& klv)
	{
		// Deprecated
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformLatitude& klv)
	{
		double UDS = dblValue;

		int LDS = (int)(0xFFFFFFFE / 180.0 * UDS);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformLongitude& klv)
	{
		double UDS = dblValue;

		int LDS = (int)(0xFFFFFFFE / 360.0 * UDS);

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformAltitude& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformName& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformHeading& klv)
	{
		double UDS = dblValue;
		UINT16 LDS = (UINT16)(0xFFFF / 360.0 * UDS);
		UINT16 nLDS = htons(LDS);
		memcpy(value, &nLDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVEventStartTimeUTC& klv)
	{
		time_t ltime = U2LFP(timestamp);
		time_t ntTime = htonll(ltime);
		memcpy(value, &ntTime, 8);
		klv.setValue(value, 8);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVRVTLocalDataSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVVMTILocalDataSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorEllipsoidHeight& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeight& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOperationalMode& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVFrameCenterHeightAboveEllipsoid& klv)
	{
		double UDS = dblValue;

		UINT16 LDS = (UINT16)(0xFFFF / 19900.0 * (UDS + 900));

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorNorthVelocity& klv)
	{
		short LDS = (short)0x8000;

		if (dblValue >= -327.0 && dblValue <= 327.0)
		{
			LDS = (short)(0xFFFE / 654.0 * dblValue);
		}

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorEastVelocity& klv)
	{
		short LDS = (short)0x8000;

		if (dblValue >= -327.0 && dblValue <= 327.0)
		{
			LDS = (short)(0xFFFE / 654.0 * dblValue);
		}

		LDS = htons(LDS);
		memcpy(value, &LDS, 2);
		klv.setValue(value, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVImageHorizonPixelPack& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLatitudePoint1Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLongitudePoint1Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLatitudePoint2Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLongitudePoint2Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLatitudePoint3Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLongitudePoint3Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLatitudePoint4Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCornerLongitudePoint4Full& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformPitchAngleFull& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformRollAngleFull& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformAngleofAttackFull& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -90.0 && UDS <= 90.0)
		{
			LDS = (int)(0xFFFFFFFE / 180.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformSideslipAngleFull& klv)
	{
		double UDS = dblValue;
		int LDS = 0x80000000;

		if (UDS >= -180.0 && UDS <= 180.0)
		{
			LDS = (int)(0xFFFFFFFE / 360.0 * UDS);
		}

		LDS = htonl(LDS);
		memcpy(value, &LDS, 4);
		klv.setValue(value, 4);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVMIISCoreIdentifier& klv)
	{
		BYTE chVer = char2int(strValue[0]) * 16 + char2int(strValue[1]);
		BYTE chUsage = char2int(strValue[2]) * 16 + char2int(strValue[3]);

		GUID uuid;
		BYTE val[18]{};
		std::string strUuid = strValue.substr(5, 36);
		unsigned char* pszUuid = (unsigned char*)strUuid.c_str();
		UuidFromStringA(pszUuid, &uuid);
		// Set up for network order;
		uuid.Data1 = htonl(uuid.Data1);
		uuid.Data2 = htons(uuid.Data2);
		uuid.Data3 = htons(uuid.Data3);
		val[0] = chVer;
		val[1] = chUsage;
		memcpy(val + 2, &uuid, 16);
		klv.setValue(val, 18);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSARMotionImageryMetadata& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetWidthExtended& klv)
	{
		BYTE val[3]{};
		FpParser fpp(0.0, 1500000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVRangeImageLocalSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVGeoRegistrationLocalSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVCompositeImagingLocalSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVSegmentLocalSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVAmendLocalSet& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVSDCCFLP& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVDensityAltitudeExtended& klv)
	{
		BYTE val[3];
		FpParser fpp(-900.0, 40000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorEllipsoidHeightExtended& klv)
	{
		BYTE val[3];
		FpParser fpp(-900.0, 40000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAlternatePlatformEllipsoidHeightExtended& klv)
	{
		BYTE val[3];
		FpParser fpp(-900.0, 40000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVStreamDesignator& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOperationalBase& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVBroadcastSource& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVRangeToRecoveryLocation& klv)
	{
		BYTE val[3];
		FpParser fpp(0.0, 21000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTimeAirborne& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVPropulsionUnitSpeed& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformCourseAngle& klv)
	{
		BYTE val[2];
		FpParser fpp(0.0, 360.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAltitudeAGL& klv)
	{
		BYTE val[3];
		FpParser fpp(-900.0, 40000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVRadarAltimeter& klv)
	{
		BYTE val[3];
		FpParser fpp(-900.0, 40000.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVControlCommand& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVControlCommandVerificationList& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorAzimuthRate& klv)
	{
		BYTE val[2];
		FpParser fpp(-1000.0, 1000.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorElevationRate& klv)
	{
		BYTE val[2];
		FpParser fpp(-1000.0, 1000.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorRollRate& klv)
	{
		BYTE val[2];
		FpParser fpp(-1000.0, 1000.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOnboardMIStoragePercentFull& klv)
	{
		BYTE val[2];
		FpParser fpp(0.0, 100.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVActiveWavelengthList& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVCountryCodes& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVNumberofNAVSATsinView& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPositioningMethodSource& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVPlatformStatus& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorControlMode& klv)
	{
		BYTE LDS = (BYTE)nValue;
		klv.setValue(&LDS, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSensorFrameRatePack& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVWavelengthsList& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVTargetID& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVAirbaseLocations& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVTakeoffTime& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVTransmissionFrequency& klv)
	{
		BYTE val[3];
		FpParser fpp(1.0, 99999.0, 3);
		fpp.encode(val, 3, dblValue);
		klv.setValue(val, 3);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVOnboardMIStorageCapacity& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVZoomPercentage& klv)
	{
		BYTE val[2];
		FpParser fpp(0.0, 100.0, 2);
		fpp.encode(val, 2, dblValue);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCommunicationsMethod& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVLeapSeconds& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVCorrectionOffset& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVPayloadList& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVActivePayloads& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVWeaponsStores& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVWaypointList& klv)
	{

	}

	void KLVEncodeVisitor::Visit(lcss::KLVObjectCountryCodingMethodVersionDate& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSecurityClassification& klv)
	{
		BYTE val = nValue;
		klv.setValue(&val, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod& klv)
	{
		BYTE val = nValue;
		klv.setValue(&val, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassifyingCountry& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVSecuritySCISHIinformation& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVCaveats& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVReleasingInstructions& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassifiedBy& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVDerivedFrom& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassificationReason& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVDeclassificationDate& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassificationandMarkingSystem& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVObjectCountryCodingMethod& klv)
	{
		BYTE val = nValue;
		klv.setValue(&val, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVObjectCountryCodes& klv)
	{
		wchar_t buf[BUFSIZ];
		size_t numOfCharConverted;
		errno_t ret = mbstowcs_s(&numOfCharConverted, buf, strValue.c_str(), BUFSIZ);
		size_t sz = (numOfCharConverted - 1) * 2;
		if (ret == 0)
		{
			BYTE valueBuf[BUFSIZ * 2]{};
			// change to network order (big-endian)
			int j = 0;
			for (int i = 0; i < numOfCharConverted - 1; i++)
			{
				unsigned short nVal;
				BYTE chVal[2];
				memcpy(&nVal, buf + i, 2);
				nVal = htons(nVal);
				memcpy(chVal, &nVal, 2);
				valueBuf[j] = chVal[0];
				valueBuf[j + 1] = chVal[1];
				j += 2;
			}
			klv.setValue(valueBuf, j);
		}
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassificationComments& klv)
	{
		encodeString(klv, strValue);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUMIDVideo& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUMIDAudio& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUMIDData& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVUMIDSystem& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVStreamID& klv)
	{
		BYTE val = nValue;
		klv.setValue(&val, 1);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVTransportStreamID& klv)
	{
		UINT16 UDS = nValue;
		UINT16 LDS = ntohs(UDS);
		BYTE val[2];
		memcpy(val, &LDS, 2);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVItemDesignator& klv)
	{
	}

	void KLVEncodeVisitor::Visit(lcss::KLVVersion& klv)
	{
		UINT16 UDS = nValue;
		UINT16 LDS = ntohs(UDS);
		BYTE val[2];
		memcpy(val, &LDS, 2);
		klv.setValue(val, 2);
	}

	void KLVEncodeVisitor::Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate& klv)
	{
		encodeString(klv, strValue);
	}

} // namespace lcss