#include "klvelmt.h"
#include "klvelmtimpl.h"
#include "klvuselmtimpl.h"
#include "decode.h"
// klvlex generated on Tue Jan 12 07:41:50 2021

int lcss::KLVElement::parse(uint8_t* buf, int size)
{
	int p = 0;
	int numOfBytesRead = 0;
	int key = decodeKey(&numOfBytesRead, buf, size);
	p = numOfBytesRead;

	switch (key)
	{
	case 1:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVChecksum);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Checksum."));
			p += len;
		}
	} break;
	case 2:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUNIXTimeStamp);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing UNIX Time Stamp."));
			p += len;
		}
	} break;
	case 3:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVMissionID);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Mission ID."));
			p += len;
		}
	} break;
	case 4:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformTailNumber);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Tail Number."));
			p += len;
		}
	} break;
	case 5:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformHeadingAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Heading Angle."));
			p += len;
		}
	} break;
	case 6:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformPitchAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Pitch Angle."));
			p += len;
		}
	} break;
	case 7:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformRollAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Roll Angle."));
			p += len;
		}
	} break;
	case 8:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformTrueAirspeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform True Airspeed."));
			p += len;
		}
	} break;
	case 9:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformIndicatedAirspeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Indicated Airspeed."));
			p += len;
		}
	} break;
	case 10:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformDesignation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Designation."));
			p += len;
		}
	} break;
	case 11:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVImageSourceSensor);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Image Source Sensor."));
			p += len;
		}
	} break;
	case 12:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVImageCoordinateSystem);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Image Coordinate System."));
			p += len;
		}
	} break;
	case 13:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorLatitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Latitude."));
			p += len;
		}
	} break;
	case 14:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorLongitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Longitude."));
			p += len;
		}
	} break;
	case 15:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorTrueAltitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor True Altitude."));
			p += len;
		}
	} break;
	case 16:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorHorizontalFieldofView);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Horizontal Field of View."));
			p += len;
		}
	} break;
	case 17:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorVerticalFieldofView);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Vertical Field of View."));
			p += len;
		}
	} break;
	case 18:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorRelativeAzimuthAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Relative Azimuth Angle."));
			p += len;
		}
	} break;
	case 19:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorRelativeElevationAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Relative Elevation Angle."));
			p += len;
		}
	} break;
	case 20:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorRelativeRollAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Relative Roll Angle."));
			p += len;
		}
	} break;
	case 21:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSlantRange);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Slant Range."));
			p += len;
		}
	} break;
	case 22:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetWidth);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Width."));
			p += len;
		}
	} break;
	case 23:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVFrameCenterLatitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Frame Center Latitude."));
			p += len;
		}
	} break;
	case 24:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVFrameCenterLongitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Frame Center Longitude."));
			p += len;
		}
	} break;
	case 25:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVFrameCenterElevation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Frame Center Elevation."));
			p += len;
		}
	} break;
	case 26:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLatitudePoint1);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Latitude Point 1."));
			p += len;
		}
	} break;
	case 27:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLongitudePoint1);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Longitude Point 1."));
			p += len;
		}
	} break;
	case 28:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLatitudePoint2);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Latitude Point 2."));
			p += len;
		}
	} break;
	case 29:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLongitudePoint2);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Longitude Point 2."));
			p += len;
		}
	} break;
	case 30:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLatitudePoint3);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Latitude Point 3."));
			p += len;
		}
	} break;
	case 31:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLongitudePoint3);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Longitude Point 3."));
			p += len;
		}
	} break;
	case 32:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLatitudePoint4);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Latitude Point 4."));
			p += len;
		}
	} break;
	case 33:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOffsetCornerLongitudePoint4);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Offset Corner Longitude Point 4."));
			p += len;
		}
	} break;
	case 34:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVIcingDetected);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Icing Detected."));
			p += len;
		}
	} break;
	case 35:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWindDirection);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Wind Direction."));
			p += len;
		}
	} break;
	case 36:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWindSpeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Wind Speed."));
			p += len;
		}
	} break;
	case 37:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVStaticPressure);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Static Pressure."));
			p += len;
		}
	} break;
	case 38:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVDensityAltitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Density Altitude."));
			p += len;
		}
	} break;
	case 39:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOutsideAirTemperature);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Outside Air Temperature."));
			p += len;
		}
	} break;
	case 40:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetLocationLatitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Location Latitude."));
			p += len;
		}
	} break;
	case 41:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetLocationLongitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Location Longitude."));
			p += len;
		}
	} break;
	case 42:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetLocationElevation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Location Elevation."));
			p += len;
		}
	} break;
	case 43:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetTrackGateWidth);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Track Gate Width."));
			p += len;
		}
	} break;
	case 44:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetTrackGateHeight);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Track Gate Height."));
			p += len;
		}
	} break;
	case 45:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetErrorEstimateCE90);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Error Estimate - CE90."));
			p += len;
		}
	} break;
	case 46:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetErrorEstimateLE90);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Error Estimate - LE90."));
			p += len;
		}
	} break;
	case 47:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVGenericFlagData01);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Generic Flag Data 01."));
			p += len;
		}
	} break;
	case 48:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSecurityLocalMetadataSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Security Local Metadata Set."));
			p += len;
		}
	} break;
	case 49:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVDifferentialPressure);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Differential Pressure."));
			p += len;
		}
	} break;
	case 50:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformAngleofAttack);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Angle of Attack."));
			p += len;
		}
	} break;
	case 51:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformVerticalSpeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Vertical Speed."));
			p += len;
		}
	} break;
	case 52:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformSideslipAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Sideslip Angle."));
			p += len;
		}
	} break;
	case 53:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAirfieldBarometicPressure);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Airfield Barometic Pressure."));
			p += len;
		}
	} break;
	case 54:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAirfieldElevation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Airfield Elevation."));
			p += len;
		}
	} break;
	case 55:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVRelativeHumidity);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Relative Humidity."));
			p += len;
		}
	} break;
	case 56:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformGroundSpeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Ground Speed."));
			p += len;
		}
	} break;
	case 57:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVGroundRange);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Ground Range."));
			p += len;
		}
	} break;
	case 58:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformFuelRemaining);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Fuel Remaining."));
			p += len;
		}
	} break;
	case 59:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformCallSign);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Call Sign."));
			p += len;
		}
	} break;
	case 60:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWeaponLoad);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Weapon Load."));
			p += len;
		}
	} break;
	case 61:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWeaponFired);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Weapon Fired."));
			p += len;
		}
	} break;
	case 62:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVLaserPRFCode);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Laser PRF Code."));
			p += len;
		}
	} break;
	case 63:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorFieldofViewName);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Field of View Name."));
			p += len;
		}
	} break;
	case 64:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformMagneticHeading);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Magnetic Heading."));
			p += len;
		}
	} break;
	case 65:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUASLDSVersionNumber);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing UAS LDS Version Number."));
			p += len;
		}
	} break;
	case 66:
	{
		int len = buf[p++];
		if (len <= 0) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetLocationCovarianceMatrix);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Location Covariance Matrix."));
			p += len;
		}
	} break;
	case 67:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformLatitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Latitude."));
			p += len;
		}
	} break;
	case 68:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformLongitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Longitude."));
			p += len;
		}
	} break;
	case 69:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformAltitude);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Altitude."));
			p += len;
		}
	} break;
	case 70:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformName);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Name."));
			p += len;
		}
	} break;
	case 71:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformHeading);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Heading."));
			p += len;
		}
	} break;
	case 72:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVEventStartTimeUTC);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Event Start Time - UTC."));
			p += len;
		}
	} break;
	case 73:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVRVTLocalDataSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing RVT Local Data Set."));
			p += len;
		}
	} break;
	case 74:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVVMTILocalDataSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing VMTI Local Data Set."));
			p += len;
		}
	} break;
	case 75:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorEllipsoidHeight);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Ellipsoid Height."));
			p += len;
		}
	} break;
	case 76:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformEllipsoidHeight);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Ellipsoid Height."));
			p += len;
		}
	} break;
	case 77:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOperationalMode);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Operational Mode."));
			p += len;
		}
	} break;
	case 78:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVFrameCenterHeightAboveEllipsoid);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Frame Center Height Above Ellipsoid."));
			p += len;
		}
	} break;
	case 79:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorNorthVelocity);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor North Velocity."));
			p += len;
		}
	} break;
	case 80:
	{
		int len = buf[p++];
		if (len <= 2) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorEastVelocity);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor East Velocity."));
			p += len;
		}
	} break;
	case 81:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVImageHorizonPixelPack);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Image Horizon Pixel Pack."));
			p += len;
		}
	} break;
	case 82:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLatitudePoint1Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Latitude Point 1 (Full)."));
			p += len;
		}
	} break;
	case 83:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLongitudePoint1Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Longitude Point 1 (Full)."));
			p += len;
		}
	} break;
	case 84:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLatitudePoint2Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Latitude Point 2 (Full)."));
			p += len;
		}
	} break;
	case 85:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLongitudePoint2Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Longitude Point 2 (Full)."));
			p += len;
		}
	} break;
	case 86:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLatitudePoint3Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Latitude Point 3 (Full)."));
			p += len;
		}
	} break;
	case 87:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLongitudePoint3Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Longitude Point 3 (Full)."));
			p += len;
		}
	} break;
	case 88:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLatitudePoint4Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Latitude Point 4 (Full)."));
			p += len;
		}
	} break;
	case 89:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCornerLongitudePoint4Full);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Corner Longitude Point 4 (Full)."));
			p += len;
		}
	} break;
	case 90:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformPitchAngleFull);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Pitch Angle (Full)."));
			p += len;
		}
	} break;
	case 91:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformRollAngleFull);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Roll Angle (Full)."));
			p += len;
		}
	} break;
	case 92:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformAngleofAttackFull);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Angle of Attack (Full)."));
			p += len;
		}
	} break;
	case 93:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformSideslipAngleFull);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Sideslip Angle (Full)."));
			p += len;
		}
	} break;
	case 94:
	{
		int len = buf[p++];
		if (len <= 50) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVMIISCoreIdentifier);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing MIIS Core Identifier."));
			p += len;
		}
	} break;
	case 95:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSARMotionImageryMetadata);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing SAR Motion Imagery Metadata."));
			p += len;
		}
	} break;
	case 96:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetWidthExtended);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target Width Extended."));
			p += len;
		}
	} break;
	case 97:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVRangeImageLocalSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Range Image Local Set."));
			p += len;
		}
	} break;
	case 98:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVGeoRegistrationLocalSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Geo-Registration Local Set."));
			p += len;
		}
	} break;
	case 99:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCompositeImagingLocalSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Composite Imaging Local Set."));
			p += len;
		}
	} break;
	case 100:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSegmentLocalSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Segment Local Set."));
			p += len;
		}
	} break;
	case 101:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAmendLocalSet);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Amend Local Set."));
			p += len;
		}
	} break;
	case 102:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSDCCFLP);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing SDCC-FLP."));
			p += len;
		}
	} break;
	case 103:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVDensityAltitudeExtended);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Density Altitude Extended."));
			p += len;
		}
	} break;
	case 104:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorEllipsoidHeightExtended);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Ellipsoid Height Extended."));
			p += len;
		}
	} break;
	case 105:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAlternatePlatformEllipsoidHeightExtended);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Alternate Platform Ellipsoid Height Extended."));
			p += len;
		}
	} break;
	case 106:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVStreamDesignator);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Stream Designator."));
			p += len;
		}
	} break;
	case 107:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOperationalBase);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Operational Base."));
			p += len;
		}
	} break;
	case 108:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVBroadcastSource);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Broadcast Source."));
			p += len;
		}
	} break;
	case 109:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVRangeToRecoveryLocation);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Range To Recovery Location."));
			p += len;
		}
	} break;
	case 110:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTimeAirborne);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Time Airborne."));
			p += len;
		}
	} break;
	case 111:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPropulsionUnitSpeed);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Propulsion Unit Speed."));
			p += len;
		}
	} break;
	case 112:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformCourseAngle);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Course Angle."));
			p += len;
		}
	} break;
	case 113:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAltitudeAGL);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Altitude AGL."));
			p += len;
		}
	} break;
	case 114:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVRadarAltimeter);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Radar Altimeter."));
			p += len;
		}
	} break;
	case 115:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVControlCommand);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Control Command."));
			p += len;
		}
	} break;
	case 116:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVControlCommandVerificationList);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Control Command Verification List."));
			p += len;
		}
	} break;
	case 117:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorAzimuthRate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Azimuth Rate."));
			p += len;
		}
	} break;
	case 118:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorElevationRate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Elevation Rate."));
			p += len;
		}
	} break;
	case 119:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorRollRate);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Roll Rate."));
			p += len;
		}
	} break;
	case 120:
	{
		int len = buf[p++];
		if (len <= 3) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOnboardMIStoragePercentFull);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing On-board MI Storage Percent Full."));
			p += len;
		}
	} break;
	case 121:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVActiveWavelengthList);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Active Wavelength List."));
			p += len;
		}
	} break;
	case 122:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCountryCodes);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Country Codes."));
			p += len;
		}
	} break;
	case 123:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVNumberofNAVSATsinView);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Number of NAVSATs in View."));
			p += len;
		}
	} break;
	case 124:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPositioningMethodSource);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Positioning Method Source."));
			p += len;
		}
	} break;
	case 125:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPlatformStatus);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Platform Status."));
			p += len;
		}
	} break;
	case 126:
	{
		int len = buf[p++];
		if (len <= 1) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorControlMode);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Control Mode."));
			p += len;
		}
	} break;
	case 127:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len <= 16) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVSensorFrameRatePack);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Sensor Frame Rate Pack."));
			p += len;
		}
	} break;
	case 128:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWavelengthsList);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Wavelengths List."));
			p += len;
		}
	} break;
	case 129:
	{
		int len = buf[p++];
		if (len <= 32) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTargetID);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Target ID."));
			p += len;
		}
	} break;
	case 130:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len <= 24) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVAirbaseLocations);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Airbase Locations."));
			p += len;
		}
	} break;
	case 131:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTakeoffTime);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Take-off Time."));
			p += len;
		}
	} break;
	case 132:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVTransmissionFrequency);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Transmission Frequency."));
			p += len;
		}
	} break;
	case 133:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVOnboardMIStorageCapacity);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing On-board MI Storage Capacity."));
			p += len;
		}
	} break;
	case 134:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVZoomPercentage);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Zoom Percentage."));
			p += len;
		}
	} break;
	case 135:
	{
		int len = buf[p++];
		if (len <= 127) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCommunicationsMethod);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Communications Method."));
			p += len;
		}
	} break;
	case 136:
	{
		int len = buf[p++];
		if (len <= 4) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVLeapSeconds);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Leap Seconds."));
			p += len;
		}
	} break;
	case 137:
	{
		int len = buf[p++];
		if (len <= 8) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVCorrectionOffset);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Correction Offset."));
			p += len;
		}
	} break;
	case 138:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVPayloadList);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Payload List."));
			p += len;
		}
	} break;
	case 139:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVActivePayloads);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Active Payloads."));
			p += len;
		}
	} break;
	case 140:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWeaponsStores);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Weapons Stores."));
			p += len;
		}
	} break;
	case 141:
	{
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		if (len < size) {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVWaypointList);
			for (size_t i = 0; i < len; i++)
				pimpl_->push_back(buf[p++]);
		}
		else {
			pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVParseError(key, "Syntax error when parsing Waypoint List."));
			p += len;
		}
	} break;
	default: {
		int len = decodeBERLength(&numOfBytesRead, buf + p, size);
		p += numOfBytesRead;
		pimpl_ = std::shared_ptr<lcss::KLVElementImpl>(new lcss::KLVUnknown(key));
		for (size_t i = 0; i < len; i++)
			pimpl_->push_back(buf[p++]);
	}
	}
	return p;
}

int lcss::KLVElement::parseUniversalSetElement(uint8_t* buf, int sz)
{
	int p = 17;
	int len = buf[16];
	uint8_t key[16];
	memcpy(key, buf, 16);
	pimpl_ = std::shared_ptr<lcss::UniversalMetadataElement>(new lcss::UniversalMetadataElement(key));
	for (size_t i = 0; i < len; i++)
		pimpl_->push_back(buf[p++]);
	return p;
}