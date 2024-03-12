#include <klvp/klvelmtimpl.h>

#include <iterator>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif
// klvlex generated on Tue Jan 12 07:41:50 2021

/////////////////////////////////////////////////////////////////////////////
// KLVElementImpl
lcss::KLVElementImpl::KLVElementImpl()
	:appData_(nullptr){}
lcss::KLVElementImpl::~KLVElementImpl(){}
uint8_t lcss::KLVElementImpl::key() const
{
	return key_.empty() ? 0 : key_[0];
}
int lcss::KLVElementImpl::key(uint8_t* keybuf) const
{
	if (keybuf == nullptr)
	{
		if (key_.size() == 16)
		{
			return 16;
		}
		else if (key_[0] < 128)
		{
			return 1;
		}
		else // key value > 127 and value < 255
		{
			return 2;
		}
	}
	else if (key_.size() == 16)
	{
#ifdef WIN32
		std::copy(key_.begin(), key_.end(), stdext::checked_array_iterator<uint8_t*>(keybuf, 16));
#else
		std::copy(key_.begin(), key_.end(), keybuf);
#endif
		return 16;
	}
	else if (key_[0] < 128)
	{
		keybuf[0] = key_[0];
		return 1;
	}
	else // key value > 127 and value < 255
	{
		keybuf[0] = 0x81;
		keybuf[1] = key() & 0x7F;
		return 2;
	}
	return 0;
}
void lcss::KLVElementImpl::setKey(uint8_t key)
{
	if (key_.empty())
		key_.push_back(key);
	else
		key_[0] = key;
}
int lcss::KLVElementImpl::length() const
{return (int)value_.size();}
int lcss::KLVElementImpl::numOfBytesForLength() const
{
	int sz = length();
	if (sz < 0x80)
		return 1;
	else if (sz > 0x7F && sz < 0x0100)
		return 2;
	else
		return 3;
}
void lcss::KLVElementImpl::value(uint8_t* buf) const
{
#ifdef WIN32
	std::copy(value_.begin(), value_.end(), stdext::checked_array_iterator<uint8_t*>(buf,length()));
#else
	std::copy(value_.begin(), value_.end(), buf);
#endif
}
uint8_t* lcss::KLVElementImpl::value() { return value_.data(); }
void lcss::KLVElementImpl::setValue(uint8_t* buf, int bufsz)
{
	value_.clear();
	for (int i = 0; i < bufsz; i++)
	{
		value_.push_back(buf[i]);
	}
}
void lcss::KLVElementImpl::push_back(uint8_t b) {value_.push_back(b);}
void* lcss::KLVElementImpl::appData() { return appData_; }
void lcss::KLVElementImpl::setAppData(void* appData) { appData_ = appData; }
int lcss::KLVElementImpl::serialize(uint8_t* buf, int bufsz) const
{
	int cur = 0;
	int state = 0;
	KLVElementImpl::const_iterator it = value_.begin();

	while (cur < bufsz)
	{
		switch (state)
		{
		case 0: // key
		{
			if (key_.size() == 16) {
				for (int i = 0; i < 16; i++) {
					buf[cur++] = key_[i];
				}
			}
			else {
				if (key() < 128) {
					buf[cur++] = key();
				}
				else {
					buf[cur++] = 0x81;
					buf[cur++] = key() & 0x7F;
				}
			}
			state++;
		} break;
		case 1: // length
		{
			if (length() < 0x7F) {
				buf[cur++] = (uint8_t)length();
			}
			else if (length() > 0x7F && length() < 0x0100) {
				buf[cur++] = 0x81;
				buf[cur++] = (uint8_t)length();
			}
			else if (length() > 0xFF && length() < 0x00010000) {
				buf[cur++] = 0x82;
				uint16_t sz = htons(length());
				uint8_t s[2];
				memcpy(s, (void*)&sz, 2);
				buf[cur++] = s[0];
				buf[cur++] = s[1];
			}
			state++;
		} break;
		case 2: // value
		{
			if (it == value_.end()) {
				goto end;
			}
			buf[cur++] = *it++;
		}break;
		}
	}
end:
	return cur;
}
lcss::UASElement::UASElement() {}
lcss::UASElement::~UASElement() {}
lcss::KLVSetElement::KLVSetElement() {}
lcss::KLVSetElement::~KLVSetElement() {}
/////////////////////////////////////////////////////////////////////////////
// KLVUnknown
lcss::KLVUnknown::KLVUnknown(uint8_t key){setKey(key);}
lcss::KLVUnknown::~KLVUnknown(){}
/////////////////////////////////////////////////////////////////////////////
// KLVParseError
lcss::KLVParseError::KLVParseError(uint8_t key,const char* msg)
	:what_(msg){setKey(key);}
lcss::KLVParseError::~KLVParseError(){}
/////////////////////////////////////////////////////////////////////////////
//KLVChecksum
lcss::KLVChecksum::KLVChecksum(){setKey(1);}
lcss::KLVChecksum::~KLVChecksum(){}
/////////////////////////////////////////////////////////////////////////////
//KLVUNIXTimeStamp
lcss::KLVUNIXTimeStamp::KLVUNIXTimeStamp(){setKey(2);}
lcss::KLVUNIXTimeStamp::~KLVUNIXTimeStamp(){}
/////////////////////////////////////////////////////////////////////////////
//KLVMissionID
lcss::KLVMissionID::KLVMissionID(){setKey(3);}
lcss::KLVMissionID::~KLVMissionID(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformTailNumber
lcss::KLVPlatformTailNumber::KLVPlatformTailNumber(){setKey(4);}
lcss::KLVPlatformTailNumber::~KLVPlatformTailNumber(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformHeadingAngle
lcss::KLVPlatformHeadingAngle::KLVPlatformHeadingAngle(){setKey(5);}
lcss::KLVPlatformHeadingAngle::~KLVPlatformHeadingAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformPitchAngle
lcss::KLVPlatformPitchAngle::KLVPlatformPitchAngle(){setKey(6);}
lcss::KLVPlatformPitchAngle::~KLVPlatformPitchAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformRollAngle
lcss::KLVPlatformRollAngle::KLVPlatformRollAngle(){setKey(7);}
lcss::KLVPlatformRollAngle::~KLVPlatformRollAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformTrueAirspeed
lcss::KLVPlatformTrueAirspeed::KLVPlatformTrueAirspeed(){setKey(8);}
lcss::KLVPlatformTrueAirspeed::~KLVPlatformTrueAirspeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformIndicatedAirspeed
lcss::KLVPlatformIndicatedAirspeed::KLVPlatformIndicatedAirspeed(){setKey(9);}
lcss::KLVPlatformIndicatedAirspeed::~KLVPlatformIndicatedAirspeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformDesignation
lcss::KLVPlatformDesignation::KLVPlatformDesignation(){setKey(10);}
lcss::KLVPlatformDesignation::~KLVPlatformDesignation(){}
/////////////////////////////////////////////////////////////////////////////
//KLVImageSourceSensor
lcss::KLVImageSourceSensor::KLVImageSourceSensor(){setKey(11);}
lcss::KLVImageSourceSensor::~KLVImageSourceSensor(){}
/////////////////////////////////////////////////////////////////////////////
//KLVImageCoordinateSystem
lcss::KLVImageCoordinateSystem::KLVImageCoordinateSystem(){setKey(12);}
lcss::KLVImageCoordinateSystem::~KLVImageCoordinateSystem(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorLatitude
lcss::KLVSensorLatitude::KLVSensorLatitude(){setKey(13);}
lcss::KLVSensorLatitude::~KLVSensorLatitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorLongitude
lcss::KLVSensorLongitude::KLVSensorLongitude(){setKey(14);}
lcss::KLVSensorLongitude::~KLVSensorLongitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorTrueAltitude
lcss::KLVSensorTrueAltitude::KLVSensorTrueAltitude(){setKey(15);}
lcss::KLVSensorTrueAltitude::~KLVSensorTrueAltitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorHorizontalFieldofView
lcss::KLVSensorHorizontalFieldofView::KLVSensorHorizontalFieldofView(){setKey(16);}
lcss::KLVSensorHorizontalFieldofView::~KLVSensorHorizontalFieldofView(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorVerticalFieldofView
lcss::KLVSensorVerticalFieldofView::KLVSensorVerticalFieldofView(){setKey(17);}
lcss::KLVSensorVerticalFieldofView::~KLVSensorVerticalFieldofView(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorRelativeAzimuthAngle
lcss::KLVSensorRelativeAzimuthAngle::KLVSensorRelativeAzimuthAngle(){setKey(18);}
lcss::KLVSensorRelativeAzimuthAngle::~KLVSensorRelativeAzimuthAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorRelativeElevationAngle
lcss::KLVSensorRelativeElevationAngle::KLVSensorRelativeElevationAngle(){setKey(19);}
lcss::KLVSensorRelativeElevationAngle::~KLVSensorRelativeElevationAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorRelativeRollAngle
lcss::KLVSensorRelativeRollAngle::KLVSensorRelativeRollAngle(){setKey(20);}
lcss::KLVSensorRelativeRollAngle::~KLVSensorRelativeRollAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSlantRange
lcss::KLVSlantRange::KLVSlantRange(){setKey(21);}
lcss::KLVSlantRange::~KLVSlantRange(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetWidth
lcss::KLVTargetWidth::KLVTargetWidth(){setKey(22);}
lcss::KLVTargetWidth::~KLVTargetWidth(){}
/////////////////////////////////////////////////////////////////////////////
//KLVFrameCenterLatitude
lcss::KLVFrameCenterLatitude::KLVFrameCenterLatitude(){setKey(23);}
lcss::KLVFrameCenterLatitude::~KLVFrameCenterLatitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVFrameCenterLongitude
lcss::KLVFrameCenterLongitude::KLVFrameCenterLongitude(){setKey(24);}
lcss::KLVFrameCenterLongitude::~KLVFrameCenterLongitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVFrameCenterElevation
lcss::KLVFrameCenterElevation::KLVFrameCenterElevation(){setKey(25);}
lcss::KLVFrameCenterElevation::~KLVFrameCenterElevation(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLatitudePoint1
lcss::KLVOffsetCornerLatitudePoint1::KLVOffsetCornerLatitudePoint1(){setKey(26);}
lcss::KLVOffsetCornerLatitudePoint1::~KLVOffsetCornerLatitudePoint1(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLongitudePoint1
lcss::KLVOffsetCornerLongitudePoint1::KLVOffsetCornerLongitudePoint1(){setKey(27);}
lcss::KLVOffsetCornerLongitudePoint1::~KLVOffsetCornerLongitudePoint1(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLatitudePoint2
lcss::KLVOffsetCornerLatitudePoint2::KLVOffsetCornerLatitudePoint2(){setKey(28);}
lcss::KLVOffsetCornerLatitudePoint2::~KLVOffsetCornerLatitudePoint2(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLongitudePoint2
lcss::KLVOffsetCornerLongitudePoint2::KLVOffsetCornerLongitudePoint2(){setKey(29);}
lcss::KLVOffsetCornerLongitudePoint2::~KLVOffsetCornerLongitudePoint2(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLatitudePoint3
lcss::KLVOffsetCornerLatitudePoint3::KLVOffsetCornerLatitudePoint3(){setKey(30);}
lcss::KLVOffsetCornerLatitudePoint3::~KLVOffsetCornerLatitudePoint3(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLongitudePoint3
lcss::KLVOffsetCornerLongitudePoint3::KLVOffsetCornerLongitudePoint3(){setKey(31);}
lcss::KLVOffsetCornerLongitudePoint3::~KLVOffsetCornerLongitudePoint3(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLatitudePoint4
lcss::KLVOffsetCornerLatitudePoint4::KLVOffsetCornerLatitudePoint4(){setKey(32);}
lcss::KLVOffsetCornerLatitudePoint4::~KLVOffsetCornerLatitudePoint4(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOffsetCornerLongitudePoint4
lcss::KLVOffsetCornerLongitudePoint4::KLVOffsetCornerLongitudePoint4(){setKey(33);}
lcss::KLVOffsetCornerLongitudePoint4::~KLVOffsetCornerLongitudePoint4(){}
/////////////////////////////////////////////////////////////////////////////
//KLVIcingDetected
lcss::KLVIcingDetected::KLVIcingDetected(){setKey(34);}
lcss::KLVIcingDetected::~KLVIcingDetected(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWindDirection
lcss::KLVWindDirection::KLVWindDirection(){setKey(35);}
lcss::KLVWindDirection::~KLVWindDirection(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWindSpeed
lcss::KLVWindSpeed::KLVWindSpeed(){setKey(36);}
lcss::KLVWindSpeed::~KLVWindSpeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVStaticPressure
lcss::KLVStaticPressure::KLVStaticPressure(){setKey(37);}
lcss::KLVStaticPressure::~KLVStaticPressure(){}
/////////////////////////////////////////////////////////////////////////////
//KLVDensityAltitude
lcss::KLVDensityAltitude::KLVDensityAltitude(){setKey(38);}
lcss::KLVDensityAltitude::~KLVDensityAltitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOutsideAirTemperature
lcss::KLVOutsideAirTemperature::KLVOutsideAirTemperature(){setKey(39);}
lcss::KLVOutsideAirTemperature::~KLVOutsideAirTemperature(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetLocationLatitude
lcss::KLVTargetLocationLatitude::KLVTargetLocationLatitude(){setKey(40);}
lcss::KLVTargetLocationLatitude::~KLVTargetLocationLatitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetLocationLongitude
lcss::KLVTargetLocationLongitude::KLVTargetLocationLongitude(){setKey(41);}
lcss::KLVTargetLocationLongitude::~KLVTargetLocationLongitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetLocationElevation
lcss::KLVTargetLocationElevation::KLVTargetLocationElevation(){setKey(42);}
lcss::KLVTargetLocationElevation::~KLVTargetLocationElevation(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetTrackGateWidth
lcss::KLVTargetTrackGateWidth::KLVTargetTrackGateWidth(){setKey(43);}
lcss::KLVTargetTrackGateWidth::~KLVTargetTrackGateWidth(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetTrackGateHeight
lcss::KLVTargetTrackGateHeight::KLVTargetTrackGateHeight(){setKey(44);}
lcss::KLVTargetTrackGateHeight::~KLVTargetTrackGateHeight(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetErrorEstimateCE90
lcss::KLVTargetErrorEstimateCE90::KLVTargetErrorEstimateCE90(){setKey(45);}
lcss::KLVTargetErrorEstimateCE90::~KLVTargetErrorEstimateCE90(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetErrorEstimateLE90
lcss::KLVTargetErrorEstimateLE90::KLVTargetErrorEstimateLE90(){setKey(46);}
lcss::KLVTargetErrorEstimateLE90::~KLVTargetErrorEstimateLE90(){}
/////////////////////////////////////////////////////////////////////////////
//KLVGenericFlagData01
lcss::KLVGenericFlagData01::KLVGenericFlagData01(){setKey(47);}
lcss::KLVGenericFlagData01::~KLVGenericFlagData01(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSecurityLocalMetadataSet
lcss::KLVSecurityLocalMetadataSet::KLVSecurityLocalMetadataSet(){setKey(48);}
lcss::KLVSecurityLocalMetadataSet::~KLVSecurityLocalMetadataSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVDifferentialPressure
lcss::KLVDifferentialPressure::KLVDifferentialPressure(){setKey(49);}
lcss::KLVDifferentialPressure::~KLVDifferentialPressure(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformAngleofAttack
lcss::KLVPlatformAngleofAttack::KLVPlatformAngleofAttack(){setKey(50);}
lcss::KLVPlatformAngleofAttack::~KLVPlatformAngleofAttack(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformVerticalSpeed
lcss::KLVPlatformVerticalSpeed::KLVPlatformVerticalSpeed(){setKey(51);}
lcss::KLVPlatformVerticalSpeed::~KLVPlatformVerticalSpeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformSideslipAngle
lcss::KLVPlatformSideslipAngle::KLVPlatformSideslipAngle(){setKey(52);}
lcss::KLVPlatformSideslipAngle::~KLVPlatformSideslipAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAirfieldBarometicPressure
lcss::KLVAirfieldBarometicPressure::KLVAirfieldBarometicPressure(){setKey(53);}
lcss::KLVAirfieldBarometicPressure::~KLVAirfieldBarometicPressure(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAirfieldElevation
lcss::KLVAirfieldElevation::KLVAirfieldElevation(){setKey(54);}
lcss::KLVAirfieldElevation::~KLVAirfieldElevation(){}
/////////////////////////////////////////////////////////////////////////////
//KLVRelativeHumidity
lcss::KLVRelativeHumidity::KLVRelativeHumidity(){setKey(55);}
lcss::KLVRelativeHumidity::~KLVRelativeHumidity(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformGroundSpeed
lcss::KLVPlatformGroundSpeed::KLVPlatformGroundSpeed(){setKey(56);}
lcss::KLVPlatformGroundSpeed::~KLVPlatformGroundSpeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVGroundRange
lcss::KLVGroundRange::KLVGroundRange(){setKey(57);}
lcss::KLVGroundRange::~KLVGroundRange(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformFuelRemaining
lcss::KLVPlatformFuelRemaining::KLVPlatformFuelRemaining(){setKey(58);}
lcss::KLVPlatformFuelRemaining::~KLVPlatformFuelRemaining(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformCallSign
lcss::KLVPlatformCallSign::KLVPlatformCallSign(){setKey(59);}
lcss::KLVPlatformCallSign::~KLVPlatformCallSign(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWeaponLoad
lcss::KLVWeaponLoad::KLVWeaponLoad(){setKey(60);}
lcss::KLVWeaponLoad::~KLVWeaponLoad(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWeaponFired
lcss::KLVWeaponFired::KLVWeaponFired(){setKey(61);}
lcss::KLVWeaponFired::~KLVWeaponFired(){}
/////////////////////////////////////////////////////////////////////////////
//KLVLaserPRFCode
lcss::KLVLaserPRFCode::KLVLaserPRFCode(){setKey(62);}
lcss::KLVLaserPRFCode::~KLVLaserPRFCode(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorFieldofViewName
lcss::KLVSensorFieldofViewName::KLVSensorFieldofViewName(){setKey(63);}
lcss::KLVSensorFieldofViewName::~KLVSensorFieldofViewName(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformMagneticHeading
lcss::KLVPlatformMagneticHeading::KLVPlatformMagneticHeading(){setKey(64);}
lcss::KLVPlatformMagneticHeading::~KLVPlatformMagneticHeading(){}
/////////////////////////////////////////////////////////////////////////////
//KLVUASLDSVersionNumber
lcss::KLVUASLDSVersionNumber::KLVUASLDSVersionNumber(){setKey(65);}
lcss::KLVUASLDSVersionNumber::~KLVUASLDSVersionNumber(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetLocationCovarianceMatrix
lcss::KLVTargetLocationCovarianceMatrix::KLVTargetLocationCovarianceMatrix(){setKey(66);}
lcss::KLVTargetLocationCovarianceMatrix::~KLVTargetLocationCovarianceMatrix(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformLatitude
lcss::KLVAlternatePlatformLatitude::KLVAlternatePlatformLatitude(){setKey(67);}
lcss::KLVAlternatePlatformLatitude::~KLVAlternatePlatformLatitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformLongitude
lcss::KLVAlternatePlatformLongitude::KLVAlternatePlatformLongitude(){setKey(68);}
lcss::KLVAlternatePlatformLongitude::~KLVAlternatePlatformLongitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformAltitude
lcss::KLVAlternatePlatformAltitude::KLVAlternatePlatformAltitude(){setKey(69);}
lcss::KLVAlternatePlatformAltitude::~KLVAlternatePlatformAltitude(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformName
lcss::KLVAlternatePlatformName::KLVAlternatePlatformName(){setKey(70);}
lcss::KLVAlternatePlatformName::~KLVAlternatePlatformName(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformHeading
lcss::KLVAlternatePlatformHeading::KLVAlternatePlatformHeading(){setKey(71);}
lcss::KLVAlternatePlatformHeading::~KLVAlternatePlatformHeading(){}
/////////////////////////////////////////////////////////////////////////////
//KLVEventStartTimeUTC
lcss::KLVEventStartTimeUTC::KLVEventStartTimeUTC(){setKey(72);}
lcss::KLVEventStartTimeUTC::~KLVEventStartTimeUTC(){}
/////////////////////////////////////////////////////////////////////////////
//KLVRVTLocalDataSet
lcss::KLVRVTLocalDataSet::KLVRVTLocalDataSet(){setKey(73);}
lcss::KLVRVTLocalDataSet::~KLVRVTLocalDataSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVVMTILocalDataSet
lcss::KLVVMTILocalDataSet::KLVVMTILocalDataSet(){setKey(74);}
lcss::KLVVMTILocalDataSet::~KLVVMTILocalDataSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorEllipsoidHeight
lcss::KLVSensorEllipsoidHeight::KLVSensorEllipsoidHeight(){setKey(75);}
lcss::KLVSensorEllipsoidHeight::~KLVSensorEllipsoidHeight(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformEllipsoidHeight
lcss::KLVAlternatePlatformEllipsoidHeight::KLVAlternatePlatformEllipsoidHeight(){setKey(76);}
lcss::KLVAlternatePlatformEllipsoidHeight::~KLVAlternatePlatformEllipsoidHeight(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOperationalMode
lcss::KLVOperationalMode::KLVOperationalMode(){setKey(77);}
lcss::KLVOperationalMode::~KLVOperationalMode(){}
/////////////////////////////////////////////////////////////////////////////
//KLVFrameCenterHeightAboveEllipsoid
lcss::KLVFrameCenterHeightAboveEllipsoid::KLVFrameCenterHeightAboveEllipsoid(){setKey(78);}
lcss::KLVFrameCenterHeightAboveEllipsoid::~KLVFrameCenterHeightAboveEllipsoid(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorNorthVelocity
lcss::KLVSensorNorthVelocity::KLVSensorNorthVelocity(){setKey(79);}
lcss::KLVSensorNorthVelocity::~KLVSensorNorthVelocity(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorEastVelocity
lcss::KLVSensorEastVelocity::KLVSensorEastVelocity(){setKey(80);}
lcss::KLVSensorEastVelocity::~KLVSensorEastVelocity(){}
/////////////////////////////////////////////////////////////////////////////
//KLVImageHorizonPixelPack
lcss::KLVImageHorizonPixelPack::KLVImageHorizonPixelPack(){setKey(81);}
lcss::KLVImageHorizonPixelPack::~KLVImageHorizonPixelPack(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLatitudePoint1Full
lcss::KLVCornerLatitudePoint1Full::KLVCornerLatitudePoint1Full(){setKey(82);}
lcss::KLVCornerLatitudePoint1Full::~KLVCornerLatitudePoint1Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLongitudePoint1Full
lcss::KLVCornerLongitudePoint1Full::KLVCornerLongitudePoint1Full(){setKey(83);}
lcss::KLVCornerLongitudePoint1Full::~KLVCornerLongitudePoint1Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLatitudePoint2Full
lcss::KLVCornerLatitudePoint2Full::KLVCornerLatitudePoint2Full(){setKey(84);}
lcss::KLVCornerLatitudePoint2Full::~KLVCornerLatitudePoint2Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLongitudePoint2Full
lcss::KLVCornerLongitudePoint2Full::KLVCornerLongitudePoint2Full(){setKey(85);}
lcss::KLVCornerLongitudePoint2Full::~KLVCornerLongitudePoint2Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLatitudePoint3Full
lcss::KLVCornerLatitudePoint3Full::KLVCornerLatitudePoint3Full(){setKey(86);}
lcss::KLVCornerLatitudePoint3Full::~KLVCornerLatitudePoint3Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLongitudePoint3Full
lcss::KLVCornerLongitudePoint3Full::KLVCornerLongitudePoint3Full(){setKey(87);}
lcss::KLVCornerLongitudePoint3Full::~KLVCornerLongitudePoint3Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLatitudePoint4Full
lcss::KLVCornerLatitudePoint4Full::KLVCornerLatitudePoint4Full(){setKey(88);}
lcss::KLVCornerLatitudePoint4Full::~KLVCornerLatitudePoint4Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCornerLongitudePoint4Full
lcss::KLVCornerLongitudePoint4Full::KLVCornerLongitudePoint4Full(){setKey(89);}
lcss::KLVCornerLongitudePoint4Full::~KLVCornerLongitudePoint4Full(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformPitchAngleFull
lcss::KLVPlatformPitchAngleFull::KLVPlatformPitchAngleFull(){setKey(90);}
lcss::KLVPlatformPitchAngleFull::~KLVPlatformPitchAngleFull(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformRollAngleFull
lcss::KLVPlatformRollAngleFull::KLVPlatformRollAngleFull(){setKey(91);}
lcss::KLVPlatformRollAngleFull::~KLVPlatformRollAngleFull(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformAngleofAttackFull
lcss::KLVPlatformAngleofAttackFull::KLVPlatformAngleofAttackFull(){setKey(92);}
lcss::KLVPlatformAngleofAttackFull::~KLVPlatformAngleofAttackFull(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformSideslipAngleFull
lcss::KLVPlatformSideslipAngleFull::KLVPlatformSideslipAngleFull(){setKey(93);}
lcss::KLVPlatformSideslipAngleFull::~KLVPlatformSideslipAngleFull(){}
/////////////////////////////////////////////////////////////////////////////
//KLVMIISCoreIdentifier
lcss::KLVMIISCoreIdentifier::KLVMIISCoreIdentifier(){setKey(94);}
lcss::KLVMIISCoreIdentifier::~KLVMIISCoreIdentifier(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSARMotionImageryMetadata
lcss::KLVSARMotionImageryMetadata::KLVSARMotionImageryMetadata(){setKey(95);}
lcss::KLVSARMotionImageryMetadata::~KLVSARMotionImageryMetadata(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetWidthExtended
lcss::KLVTargetWidthExtended::KLVTargetWidthExtended(){setKey(96);}
lcss::KLVTargetWidthExtended::~KLVTargetWidthExtended(){}
/////////////////////////////////////////////////////////////////////////////
//KLVRangeImageLocalSet
lcss::KLVRangeImageLocalSet::KLVRangeImageLocalSet(){setKey(97);}
lcss::KLVRangeImageLocalSet::~KLVRangeImageLocalSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVGeoRegistrationLocalSet
lcss::KLVGeoRegistrationLocalSet::KLVGeoRegistrationLocalSet(){setKey(98);}
lcss::KLVGeoRegistrationLocalSet::~KLVGeoRegistrationLocalSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCompositeImagingLocalSet
lcss::KLVCompositeImagingLocalSet::KLVCompositeImagingLocalSet(){setKey(99);}
lcss::KLVCompositeImagingLocalSet::~KLVCompositeImagingLocalSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSegmentLocalSet
lcss::KLVSegmentLocalSet::KLVSegmentLocalSet(){setKey(100);}
lcss::KLVSegmentLocalSet::~KLVSegmentLocalSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAmendLocalSet
lcss::KLVAmendLocalSet::KLVAmendLocalSet(){setKey(101);}
lcss::KLVAmendLocalSet::~KLVAmendLocalSet(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSDCCFLP
lcss::KLVSDCCFLP::KLVSDCCFLP(){setKey(102);}
lcss::KLVSDCCFLP::~KLVSDCCFLP(){}
/////////////////////////////////////////////////////////////////////////////
//KLVDensityAltitudeExtended
lcss::KLVDensityAltitudeExtended::KLVDensityAltitudeExtended(){setKey(103);}
lcss::KLVDensityAltitudeExtended::~KLVDensityAltitudeExtended(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorEllipsoidHeightExtended
lcss::KLVSensorEllipsoidHeightExtended::KLVSensorEllipsoidHeightExtended(){setKey(104);}
lcss::KLVSensorEllipsoidHeightExtended::~KLVSensorEllipsoidHeightExtended(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAlternatePlatformEllipsoidHeightExtended
lcss::KLVAlternatePlatformEllipsoidHeightExtended::KLVAlternatePlatformEllipsoidHeightExtended(){setKey(105);}
lcss::KLVAlternatePlatformEllipsoidHeightExtended::~KLVAlternatePlatformEllipsoidHeightExtended(){}
/////////////////////////////////////////////////////////////////////////////
//KLVStreamDesignator
lcss::KLVStreamDesignator::KLVStreamDesignator(){setKey(106);}
lcss::KLVStreamDesignator::~KLVStreamDesignator(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOperationalBase
lcss::KLVOperationalBase::KLVOperationalBase(){setKey(107);}
lcss::KLVOperationalBase::~KLVOperationalBase(){}
/////////////////////////////////////////////////////////////////////////////
//KLVBroadcastSource
lcss::KLVBroadcastSource::KLVBroadcastSource(){setKey(108);}
lcss::KLVBroadcastSource::~KLVBroadcastSource(){}
/////////////////////////////////////////////////////////////////////////////
//KLVRangeToRecoveryLocation
lcss::KLVRangeToRecoveryLocation::KLVRangeToRecoveryLocation(){setKey(109);}
lcss::KLVRangeToRecoveryLocation::~KLVRangeToRecoveryLocation(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTimeAirborne
lcss::KLVTimeAirborne::KLVTimeAirborne(){setKey(110);}
lcss::KLVTimeAirborne::~KLVTimeAirborne(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPropulsionUnitSpeed
lcss::KLVPropulsionUnitSpeed::KLVPropulsionUnitSpeed(){setKey(111);}
lcss::KLVPropulsionUnitSpeed::~KLVPropulsionUnitSpeed(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformCourseAngle
lcss::KLVPlatformCourseAngle::KLVPlatformCourseAngle(){setKey(112);}
lcss::KLVPlatformCourseAngle::~KLVPlatformCourseAngle(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAltitudeAGL
lcss::KLVAltitudeAGL::KLVAltitudeAGL(){setKey(113);}
lcss::KLVAltitudeAGL::~KLVAltitudeAGL(){}
/////////////////////////////////////////////////////////////////////////////
//KLVRadarAltimeter
lcss::KLVRadarAltimeter::KLVRadarAltimeter(){setKey(114);}
lcss::KLVRadarAltimeter::~KLVRadarAltimeter(){}
/////////////////////////////////////////////////////////////////////////////
//KLVControlCommand
lcss::KLVControlCommand::KLVControlCommand(){setKey(115);}
lcss::KLVControlCommand::~KLVControlCommand(){}
/////////////////////////////////////////////////////////////////////////////
//KLVControlCommandVerificationList
lcss::KLVControlCommandVerificationList::KLVControlCommandVerificationList(){setKey(116);}
lcss::KLVControlCommandVerificationList::~KLVControlCommandVerificationList(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorAzimuthRate
lcss::KLVSensorAzimuthRate::KLVSensorAzimuthRate(){setKey(117);}
lcss::KLVSensorAzimuthRate::~KLVSensorAzimuthRate(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorElevationRate
lcss::KLVSensorElevationRate::KLVSensorElevationRate(){setKey(118);}
lcss::KLVSensorElevationRate::~KLVSensorElevationRate(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorRollRate
lcss::KLVSensorRollRate::KLVSensorRollRate(){setKey(119);}
lcss::KLVSensorRollRate::~KLVSensorRollRate(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOnboardMIStoragePercentFull
lcss::KLVOnboardMIStoragePercentFull::KLVOnboardMIStoragePercentFull(){setKey(120);}
lcss::KLVOnboardMIStoragePercentFull::~KLVOnboardMIStoragePercentFull(){}
/////////////////////////////////////////////////////////////////////////////
//KLVActiveWavelengthList
lcss::KLVActiveWavelengthList::KLVActiveWavelengthList(){setKey(121);}
lcss::KLVActiveWavelengthList::~KLVActiveWavelengthList(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCountryCodes
lcss::KLVCountryCodes::KLVCountryCodes(){setKey(122);}
lcss::KLVCountryCodes::~KLVCountryCodes(){}
/////////////////////////////////////////////////////////////////////////////
//KLVNumberofNAVSATsinView
lcss::KLVNumberofNAVSATsinView::KLVNumberofNAVSATsinView(){setKey(123);}
lcss::KLVNumberofNAVSATsinView::~KLVNumberofNAVSATsinView(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPositioningMethodSource
lcss::KLVPositioningMethodSource::KLVPositioningMethodSource(){setKey(124);}
lcss::KLVPositioningMethodSource::~KLVPositioningMethodSource(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPlatformStatus
lcss::KLVPlatformStatus::KLVPlatformStatus(){setKey(125);}
lcss::KLVPlatformStatus::~KLVPlatformStatus(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorControlMode
lcss::KLVSensorControlMode::KLVSensorControlMode(){setKey(126);}
lcss::KLVSensorControlMode::~KLVSensorControlMode(){}
/////////////////////////////////////////////////////////////////////////////
//KLVSensorFrameRatePack
lcss::KLVSensorFrameRatePack::KLVSensorFrameRatePack(){setKey(127);}
lcss::KLVSensorFrameRatePack::~KLVSensorFrameRatePack(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWavelengthsList
lcss::KLVWavelengthsList::KLVWavelengthsList(){setKey(128);}
lcss::KLVWavelengthsList::~KLVWavelengthsList(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTargetID
lcss::KLVTargetID::KLVTargetID(){setKey(129);}
lcss::KLVTargetID::~KLVTargetID(){}
/////////////////////////////////////////////////////////////////////////////
//KLVAirbaseLocations
lcss::KLVAirbaseLocations::KLVAirbaseLocations(){setKey(130);}
lcss::KLVAirbaseLocations::~KLVAirbaseLocations(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTakeoffTime
lcss::KLVTakeoffTime::KLVTakeoffTime(){setKey(131);}
lcss::KLVTakeoffTime::~KLVTakeoffTime(){}
/////////////////////////////////////////////////////////////////////////////
//KLVTransmissionFrequency
lcss::KLVTransmissionFrequency::KLVTransmissionFrequency(){setKey(132);}
lcss::KLVTransmissionFrequency::~KLVTransmissionFrequency(){}
/////////////////////////////////////////////////////////////////////////////
//KLVOnboardMIStorageCapacity
lcss::KLVOnboardMIStorageCapacity::KLVOnboardMIStorageCapacity(){setKey(133);}
lcss::KLVOnboardMIStorageCapacity::~KLVOnboardMIStorageCapacity(){}
/////////////////////////////////////////////////////////////////////////////
//KLVZoomPercentage
lcss::KLVZoomPercentage::KLVZoomPercentage(){setKey(134);}
lcss::KLVZoomPercentage::~KLVZoomPercentage(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCommunicationsMethod
lcss::KLVCommunicationsMethod::KLVCommunicationsMethod(){setKey(135);}
lcss::KLVCommunicationsMethod::~KLVCommunicationsMethod(){}
/////////////////////////////////////////////////////////////////////////////
//KLVLeapSeconds
lcss::KLVLeapSeconds::KLVLeapSeconds(){setKey(136);}
lcss::KLVLeapSeconds::~KLVLeapSeconds(){}
/////////////////////////////////////////////////////////////////////////////
//KLVCorrectionOffset
lcss::KLVCorrectionOffset::KLVCorrectionOffset(){setKey(137);}
lcss::KLVCorrectionOffset::~KLVCorrectionOffset(){}
/////////////////////////////////////////////////////////////////////////////
//KLVPayloadList
lcss::KLVPayloadList::KLVPayloadList(){setKey(138);}
lcss::KLVPayloadList::~KLVPayloadList(){}
/////////////////////////////////////////////////////////////////////////////
//KLVActivePayloads
lcss::KLVActivePayloads::KLVActivePayloads(){setKey(139);}
lcss::KLVActivePayloads::~KLVActivePayloads(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWeaponsStores
lcss::KLVWeaponsStores::KLVWeaponsStores(){setKey(140);}
lcss::KLVWeaponsStores::~KLVWeaponsStores(){}
/////////////////////////////////////////////////////////////////////////////
//KLVWaypointList
lcss::KLVWaypointList::KLVWaypointList(){setKey(141);}
lcss::KLVWaypointList::~KLVWaypointList(){}
