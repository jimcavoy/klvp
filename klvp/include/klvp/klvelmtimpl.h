#ifndef KLVELMTIMPL_H 
#define KLVELMTIMPL_H 
// klvlex generated on Tue Jan 12 07:41:50 2021


/// @file klvelmtimpl.h
///
/// Contains KLVElementImpl class definition and all its derived classes that 
/// implement KLV element types specified in MISB ST 0601.

#include <loki/Visitor.h>
#include <vector>
#include <string>
#include <cstdint>

#define LIBKLVP_DEFINE_VISITABLE(baseclass) \
    virtual ReturnType Accept(::Loki::BaseVisitor& guest) \
    { AcceptImpl(*this, guest); \
      return AcceptImpl((baseclass&) * this, guest); }

namespace lcss
{
	/////////////////////////////////////////////////////////////////////////////
	// KLVElementImpl

	/// @brief Definition for the base implementation class KLVElementImpl that 
	/// all derived classes share
	class KLVElementImpl
		:public Loki::BaseVisitable<>
	{
	public:
		typedef std::vector<uint8_t> RawByteValue;
		typedef RawByteValue::iterator iterator;
		typedef RawByteValue::const_iterator const_iterator;
	public:
		KLVElementImpl();
		virtual ~KLVElementImpl();

		uint8_t key() const;
		int key(uint8_t* keybuf) const;
		void setKey(uint8_t k);
		int length() const;
		int numOfBytesForLength() const;
		void value(uint8_t*) const;
		uint8_t* value();
		void setValue(uint8_t* buf, int bufsz);
		int serialize(uint8_t* buf, int bufsz) const;
		void push_back(uint8_t);

		void* appData();
		void setAppData(void* appData);

	protected:
		RawByteValue	key_;
		RawByteValue	value_;
		void* appData_;
	};
	/////////////////////////////////////////////////////////////////////////////
	// KLVUnknown
	class KLVUnknown
		:public KLVElementImpl
	{
	public:
		KLVUnknown(uint8_t key);
		virtual ~KLVUnknown();
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	// KLVParseError
	class KLVParseError
		:public KLVElementImpl
	{
	public:
		KLVParseError(uint8_t key, const char* msg);
		virtual ~KLVParseError();
		std::string what_;
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	// UASElement
	class UASElement
		:public KLVElementImpl
	{
	public:
		UASElement();
		virtual ~UASElement();
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	// KLVSetElement
	class KLVSetElement
		:public KLVElementImpl
	{
	public:
		KLVSetElement();
		virtual ~KLVSetElement();
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVChecksum
	class KLVChecksum
		:public UASElement
	{
	public:
		KLVChecksum();
		virtual ~KLVChecksum();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUNIXTimeStamp
	class KLVUNIXTimeStamp
		:public UASElement
	{
	public:
		KLVUNIXTimeStamp();
		virtual ~KLVUNIXTimeStamp();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVMissionID
	class KLVMissionID
		:public UASElement
	{
	public:
		KLVMissionID();
		virtual ~KLVMissionID();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformTailNumber
	class KLVPlatformTailNumber
		:public UASElement
	{
	public:
		KLVPlatformTailNumber();
		virtual ~KLVPlatformTailNumber();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformHeadingAngle
	class KLVPlatformHeadingAngle
		:public UASElement
	{
	public:
		KLVPlatformHeadingAngle();
		virtual ~KLVPlatformHeadingAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformPitchAngle
	class KLVPlatformPitchAngle
		:public UASElement
	{
	public:
		KLVPlatformPitchAngle();
		virtual ~KLVPlatformPitchAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformRollAngle
	class KLVPlatformRollAngle
		:public UASElement
	{
	public:
		KLVPlatformRollAngle();
		virtual ~KLVPlatformRollAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformTrueAirspeed
	class KLVPlatformTrueAirspeed
		:public UASElement
	{
	public:
		KLVPlatformTrueAirspeed();
		virtual ~KLVPlatformTrueAirspeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformIndicatedAirspeed
	class KLVPlatformIndicatedAirspeed
		:public UASElement
	{
	public:
		KLVPlatformIndicatedAirspeed();
		virtual ~KLVPlatformIndicatedAirspeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformDesignation
	class KLVPlatformDesignation
		:public UASElement
	{
	public:
		KLVPlatformDesignation();
		virtual ~KLVPlatformDesignation();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVImageSourceSensor
	class KLVImageSourceSensor
		:public UASElement
	{
	public:
		KLVImageSourceSensor();
		virtual ~KLVImageSourceSensor();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVImageCoordinateSystem
	class KLVImageCoordinateSystem
		:public UASElement
	{
	public:
		KLVImageCoordinateSystem();
		virtual ~KLVImageCoordinateSystem();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorLatitude
	class KLVSensorLatitude
		:public UASElement
	{
	public:
		KLVSensorLatitude();
		virtual ~KLVSensorLatitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorLongitude
	class KLVSensorLongitude
		:public UASElement
	{
	public:
		KLVSensorLongitude();
		virtual ~KLVSensorLongitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorTrueAltitude
	class KLVSensorTrueAltitude
		:public UASElement
	{
	public:
		KLVSensorTrueAltitude();
		virtual ~KLVSensorTrueAltitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorHorizontalFieldofView
	class KLVSensorHorizontalFieldofView
		:public UASElement
	{
	public:
		KLVSensorHorizontalFieldofView();
		virtual ~KLVSensorHorizontalFieldofView();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorVerticalFieldofView
	class KLVSensorVerticalFieldofView
		:public UASElement
	{
	public:
		KLVSensorVerticalFieldofView();
		virtual ~KLVSensorVerticalFieldofView();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorRelativeAzimuthAngle
	class KLVSensorRelativeAzimuthAngle
		:public UASElement
	{
	public:
		KLVSensorRelativeAzimuthAngle();
		virtual ~KLVSensorRelativeAzimuthAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorRelativeElevationAngle
	class KLVSensorRelativeElevationAngle
		:public UASElement
	{
	public:
		KLVSensorRelativeElevationAngle();
		virtual ~KLVSensorRelativeElevationAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorRelativeRollAngle
	class KLVSensorRelativeRollAngle
		:public UASElement
	{
	public:
		KLVSensorRelativeRollAngle();
		virtual ~KLVSensorRelativeRollAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSlantRange
	class KLVSlantRange
		:public UASElement
	{
	public:
		KLVSlantRange();
		virtual ~KLVSlantRange();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetWidth
	class KLVTargetWidth
		:public UASElement
	{
	public:
		KLVTargetWidth();
		virtual ~KLVTargetWidth();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVFrameCenterLatitude
	class KLVFrameCenterLatitude
		:public UASElement
	{
	public:
		KLVFrameCenterLatitude();
		virtual ~KLVFrameCenterLatitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVFrameCenterLongitude
	class KLVFrameCenterLongitude
		:public UASElement
	{
	public:
		KLVFrameCenterLongitude();
		virtual ~KLVFrameCenterLongitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVFrameCenterElevation
	class KLVFrameCenterElevation
		:public UASElement
	{
	public:
		KLVFrameCenterElevation();
		virtual ~KLVFrameCenterElevation();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLatitudePoint1
	class KLVOffsetCornerLatitudePoint1
		:public UASElement
	{
	public:
		KLVOffsetCornerLatitudePoint1();
		virtual ~KLVOffsetCornerLatitudePoint1();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLongitudePoint1
	class KLVOffsetCornerLongitudePoint1
		:public UASElement
	{
	public:
		KLVOffsetCornerLongitudePoint1();
		virtual ~KLVOffsetCornerLongitudePoint1();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLatitudePoint2
	class KLVOffsetCornerLatitudePoint2
		:public UASElement
	{
	public:
		KLVOffsetCornerLatitudePoint2();
		virtual ~KLVOffsetCornerLatitudePoint2();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLongitudePoint2
	class KLVOffsetCornerLongitudePoint2
		:public UASElement
	{
	public:
		KLVOffsetCornerLongitudePoint2();
		virtual ~KLVOffsetCornerLongitudePoint2();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLatitudePoint3
	class KLVOffsetCornerLatitudePoint3
		:public UASElement
	{
	public:
		KLVOffsetCornerLatitudePoint3();
		virtual ~KLVOffsetCornerLatitudePoint3();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLongitudePoint3
	class KLVOffsetCornerLongitudePoint3
		:public UASElement
	{
	public:
		KLVOffsetCornerLongitudePoint3();
		virtual ~KLVOffsetCornerLongitudePoint3();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLatitudePoint4
	class KLVOffsetCornerLatitudePoint4
		:public UASElement
	{
	public:
		KLVOffsetCornerLatitudePoint4();
		virtual ~KLVOffsetCornerLatitudePoint4();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOffsetCornerLongitudePoint4
	class KLVOffsetCornerLongitudePoint4
		:public UASElement
	{
	public:
		KLVOffsetCornerLongitudePoint4();
		virtual ~KLVOffsetCornerLongitudePoint4();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVIcingDetected
	class KLVIcingDetected
		:public UASElement
	{
	public:
		KLVIcingDetected();
		virtual ~KLVIcingDetected();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWindDirection
	class KLVWindDirection
		:public UASElement
	{
	public:
		KLVWindDirection();
		virtual ~KLVWindDirection();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWindSpeed
	class KLVWindSpeed
		:public UASElement
	{
	public:
		KLVWindSpeed();
		virtual ~KLVWindSpeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVStaticPressure
	class KLVStaticPressure
		:public UASElement
	{
	public:
		KLVStaticPressure();
		virtual ~KLVStaticPressure();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVDensityAltitude
	class KLVDensityAltitude
		:public UASElement
	{
	public:
		KLVDensityAltitude();
		virtual ~KLVDensityAltitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOutsideAirTemperature
	class KLVOutsideAirTemperature
		:public UASElement
	{
	public:
		KLVOutsideAirTemperature();
		virtual ~KLVOutsideAirTemperature();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetLocationLatitude
	class KLVTargetLocationLatitude
		:public UASElement
	{
	public:
		KLVTargetLocationLatitude();
		virtual ~KLVTargetLocationLatitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetLocationLongitude
	class KLVTargetLocationLongitude
		:public UASElement
	{
	public:
		KLVTargetLocationLongitude();
		virtual ~KLVTargetLocationLongitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetLocationElevation
	class KLVTargetLocationElevation
		:public UASElement
	{
	public:
		KLVTargetLocationElevation();
		virtual ~KLVTargetLocationElevation();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetTrackGateWidth
	class KLVTargetTrackGateWidth
		:public UASElement
	{
	public:
		KLVTargetTrackGateWidth();
		virtual ~KLVTargetTrackGateWidth();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetTrackGateHeight
	class KLVTargetTrackGateHeight
		:public UASElement
	{
	public:
		KLVTargetTrackGateHeight();
		virtual ~KLVTargetTrackGateHeight();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetErrorEstimateCE90
	class KLVTargetErrorEstimateCE90
		:public UASElement
	{
	public:
		KLVTargetErrorEstimateCE90();
		virtual ~KLVTargetErrorEstimateCE90();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetErrorEstimateLE90
	class KLVTargetErrorEstimateLE90
		:public UASElement
	{
	public:
		KLVTargetErrorEstimateLE90();
		virtual ~KLVTargetErrorEstimateLE90();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVGenericFlagData01
	class KLVGenericFlagData01
		:public UASElement
	{
	public:
		KLVGenericFlagData01();
		virtual ~KLVGenericFlagData01();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSecurityLocalMetadataSet
	class KLVSecurityLocalMetadataSet
		:public KLVSetElement
	{
	public:
		KLVSecurityLocalMetadataSet();
		virtual ~KLVSecurityLocalMetadataSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVDifferentialPressure
	class KLVDifferentialPressure
		:public UASElement
	{
	public:
		KLVDifferentialPressure();
		virtual ~KLVDifferentialPressure();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformAngleofAttack
	class KLVPlatformAngleofAttack
		:public UASElement
	{
	public:
		KLVPlatformAngleofAttack();
		virtual ~KLVPlatformAngleofAttack();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformVerticalSpeed
	class KLVPlatformVerticalSpeed
		:public UASElement
	{
	public:
		KLVPlatformVerticalSpeed();
		virtual ~KLVPlatformVerticalSpeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformSideslipAngle
	class KLVPlatformSideslipAngle
		:public UASElement
	{
	public:
		KLVPlatformSideslipAngle();
		virtual ~KLVPlatformSideslipAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAirfieldBarometicPressure
	class KLVAirfieldBarometicPressure
		:public UASElement
	{
	public:
		KLVAirfieldBarometicPressure();
		virtual ~KLVAirfieldBarometicPressure();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAirfieldElevation
	class KLVAirfieldElevation
		:public UASElement
	{
	public:
		KLVAirfieldElevation();
		virtual ~KLVAirfieldElevation();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVRelativeHumidity
	class KLVRelativeHumidity
		:public UASElement
	{
	public:
		KLVRelativeHumidity();
		virtual ~KLVRelativeHumidity();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformGroundSpeed
	class KLVPlatformGroundSpeed
		:public UASElement
	{
	public:
		KLVPlatformGroundSpeed();
		virtual ~KLVPlatformGroundSpeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVGroundRange
	class KLVGroundRange
		:public UASElement
	{
	public:
		KLVGroundRange();
		virtual ~KLVGroundRange();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformFuelRemaining
	class KLVPlatformFuelRemaining
		:public UASElement
	{
	public:
		KLVPlatformFuelRemaining();
		virtual ~KLVPlatformFuelRemaining();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformCallSign
	class KLVPlatformCallSign
		:public UASElement
	{
	public:
		KLVPlatformCallSign();
		virtual ~KLVPlatformCallSign();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWeaponLoad
	class KLVWeaponLoad
		:public UASElement
	{
	public:
		KLVWeaponLoad();
		virtual ~KLVWeaponLoad();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWeaponFired
	class KLVWeaponFired
		:public UASElement
	{
	public:
		KLVWeaponFired();
		virtual ~KLVWeaponFired();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVLaserPRFCode
	class KLVLaserPRFCode
		:public UASElement
	{
	public:
		KLVLaserPRFCode();
		virtual ~KLVLaserPRFCode();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorFieldofViewName
	class KLVSensorFieldofViewName
		:public UASElement
	{
	public:
		KLVSensorFieldofViewName();
		virtual ~KLVSensorFieldofViewName();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformMagneticHeading
	class KLVPlatformMagneticHeading
		:public UASElement
	{
	public:
		KLVPlatformMagneticHeading();
		virtual ~KLVPlatformMagneticHeading();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUASLDSVersionNumber
	class KLVUASLDSVersionNumber
		:public UASElement
	{
	public:
		KLVUASLDSVersionNumber();
		virtual ~KLVUASLDSVersionNumber();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetLocationCovarianceMatrix
	class KLVTargetLocationCovarianceMatrix
		:public UASElement
	{
	public:
		KLVTargetLocationCovarianceMatrix();
		virtual ~KLVTargetLocationCovarianceMatrix();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformLatitude
	class KLVAlternatePlatformLatitude
		:public UASElement
	{
	public:
		KLVAlternatePlatformLatitude();
		virtual ~KLVAlternatePlatformLatitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformLongitude
	class KLVAlternatePlatformLongitude
		:public UASElement
	{
	public:
		KLVAlternatePlatformLongitude();
		virtual ~KLVAlternatePlatformLongitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformAltitude
	class KLVAlternatePlatformAltitude
		:public UASElement
	{
	public:
		KLVAlternatePlatformAltitude();
		virtual ~KLVAlternatePlatformAltitude();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformName
	class KLVAlternatePlatformName
		:public UASElement
	{
	public:
		KLVAlternatePlatformName();
		virtual ~KLVAlternatePlatformName();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformHeading
	class KLVAlternatePlatformHeading
		:public UASElement
	{
	public:
		KLVAlternatePlatformHeading();
		virtual ~KLVAlternatePlatformHeading();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVEventStartTimeUTC
	class KLVEventStartTimeUTC
		:public UASElement
	{
	public:
		KLVEventStartTimeUTC();
		virtual ~KLVEventStartTimeUTC();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVRVTLocalDataSet
	class KLVRVTLocalDataSet
		:public KLVSetElement
	{
	public:
		KLVRVTLocalDataSet();
		virtual ~KLVRVTLocalDataSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVVMTILocalDataSet
	class KLVVMTILocalDataSet
		:public KLVSetElement
	{
	public:
		KLVVMTILocalDataSet();
		virtual ~KLVVMTILocalDataSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorEllipsoidHeight
	class KLVSensorEllipsoidHeight
		:public UASElement
	{
	public:
		KLVSensorEllipsoidHeight();
		virtual ~KLVSensorEllipsoidHeight();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformEllipsoidHeight
	class KLVAlternatePlatformEllipsoidHeight
		:public UASElement
	{
	public:
		KLVAlternatePlatformEllipsoidHeight();
		virtual ~KLVAlternatePlatformEllipsoidHeight();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOperationalMode
	class KLVOperationalMode
		:public UASElement
	{
	public:
		KLVOperationalMode();
		virtual ~KLVOperationalMode();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVFrameCenterHeightAboveEllipsoid
	class KLVFrameCenterHeightAboveEllipsoid
		:public UASElement
	{
	public:
		KLVFrameCenterHeightAboveEllipsoid();
		virtual ~KLVFrameCenterHeightAboveEllipsoid();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorNorthVelocity
	class KLVSensorNorthVelocity
		:public UASElement
	{
	public:
		KLVSensorNorthVelocity();
		virtual ~KLVSensorNorthVelocity();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorEastVelocity
	class KLVSensorEastVelocity
		:public UASElement
	{
	public:
		KLVSensorEastVelocity();
		virtual ~KLVSensorEastVelocity();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVImageHorizonPixelPack
	class KLVImageHorizonPixelPack
		:public UASElement
	{
	public:
		KLVImageHorizonPixelPack();
		virtual ~KLVImageHorizonPixelPack();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLatitudePoint1Full
	class KLVCornerLatitudePoint1Full
		:public UASElement
	{
	public:
		KLVCornerLatitudePoint1Full();
		virtual ~KLVCornerLatitudePoint1Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLongitudePoint1Full
	class KLVCornerLongitudePoint1Full
		:public UASElement
	{
	public:
		KLVCornerLongitudePoint1Full();
		virtual ~KLVCornerLongitudePoint1Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLatitudePoint2Full
	class KLVCornerLatitudePoint2Full
		:public UASElement
	{
	public:
		KLVCornerLatitudePoint2Full();
		virtual ~KLVCornerLatitudePoint2Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLongitudePoint2Full
	class KLVCornerLongitudePoint2Full
		:public UASElement
	{
	public:
		KLVCornerLongitudePoint2Full();
		virtual ~KLVCornerLongitudePoint2Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLatitudePoint3Full
	class KLVCornerLatitudePoint3Full
		:public UASElement
	{
	public:
		KLVCornerLatitudePoint3Full();
		virtual ~KLVCornerLatitudePoint3Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLongitudePoint3Full
	class KLVCornerLongitudePoint3Full
		:public UASElement
	{
	public:
		KLVCornerLongitudePoint3Full();
		virtual ~KLVCornerLongitudePoint3Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLatitudePoint4Full
	class KLVCornerLatitudePoint4Full
		:public UASElement
	{
	public:
		KLVCornerLatitudePoint4Full();
		virtual ~KLVCornerLatitudePoint4Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCornerLongitudePoint4Full
	class KLVCornerLongitudePoint4Full
		:public UASElement
	{
	public:
		KLVCornerLongitudePoint4Full();
		virtual ~KLVCornerLongitudePoint4Full();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformPitchAngleFull
	class KLVPlatformPitchAngleFull
		:public UASElement
	{
	public:
		KLVPlatformPitchAngleFull();
		virtual ~KLVPlatformPitchAngleFull();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformRollAngleFull
	class KLVPlatformRollAngleFull
		:public UASElement
	{
	public:
		KLVPlatformRollAngleFull();
		virtual ~KLVPlatformRollAngleFull();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformAngleofAttackFull
	class KLVPlatformAngleofAttackFull
		:public UASElement
	{
	public:
		KLVPlatformAngleofAttackFull();
		virtual ~KLVPlatformAngleofAttackFull();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformSideslipAngleFull
	class KLVPlatformSideslipAngleFull
		:public UASElement
	{
	public:
		KLVPlatformSideslipAngleFull();
		virtual ~KLVPlatformSideslipAngleFull();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVMIISCoreIdentifier
	class KLVMIISCoreIdentifier
		:public UASElement
	{
	public:
		KLVMIISCoreIdentifier();
		virtual ~KLVMIISCoreIdentifier();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSARMotionImageryMetadata
	class KLVSARMotionImageryMetadata
		:public KLVSetElement
	{
	public:
		KLVSARMotionImageryMetadata();
		virtual ~KLVSARMotionImageryMetadata();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetWidthExtended
	class KLVTargetWidthExtended
		:public UASElement
	{
	public:
		KLVTargetWidthExtended();
		virtual ~KLVTargetWidthExtended();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVRangeImageLocalSet
	class KLVRangeImageLocalSet
		:public KLVSetElement
	{
	public:
		KLVRangeImageLocalSet();
		virtual ~KLVRangeImageLocalSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVGeoRegistrationLocalSet
	class KLVGeoRegistrationLocalSet
		:public KLVSetElement
	{
	public:
		KLVGeoRegistrationLocalSet();
		virtual ~KLVGeoRegistrationLocalSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCompositeImagingLocalSet
	class KLVCompositeImagingLocalSet
		:public KLVSetElement
	{
	public:
		KLVCompositeImagingLocalSet();
		virtual ~KLVCompositeImagingLocalSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSegmentLocalSet
	class KLVSegmentLocalSet
		:public KLVSetElement
	{
	public:
		KLVSegmentLocalSet();
		virtual ~KLVSegmentLocalSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAmendLocalSet
	class KLVAmendLocalSet
		:public KLVSetElement
	{
	public:
		KLVAmendLocalSet();
		virtual ~KLVAmendLocalSet();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSetElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSDCCFLP
	class KLVSDCCFLP
		:public UASElement
	{
	public:
		KLVSDCCFLP();
		virtual ~KLVSDCCFLP();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVDensityAltitudeExtended
	class KLVDensityAltitudeExtended
		:public UASElement
	{
	public:
		KLVDensityAltitudeExtended();
		virtual ~KLVDensityAltitudeExtended();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorEllipsoidHeightExtended
	class KLVSensorEllipsoidHeightExtended
		:public UASElement
	{
	public:
		KLVSensorEllipsoidHeightExtended();
		virtual ~KLVSensorEllipsoidHeightExtended();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAlternatePlatformEllipsoidHeightExtended
	class KLVAlternatePlatformEllipsoidHeightExtended
		:public UASElement
	{
	public:
		KLVAlternatePlatformEllipsoidHeightExtended();
		virtual ~KLVAlternatePlatformEllipsoidHeightExtended();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVStreamDesignator
	class KLVStreamDesignator
		:public UASElement
	{
	public:
		KLVStreamDesignator();
		virtual ~KLVStreamDesignator();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOperationalBase
	class KLVOperationalBase
		:public UASElement
	{
	public:
		KLVOperationalBase();
		virtual ~KLVOperationalBase();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVBroadcastSource
	class KLVBroadcastSource
		:public UASElement
	{
	public:
		KLVBroadcastSource();
		virtual ~KLVBroadcastSource();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVRangeToRecoveryLocation
	class KLVRangeToRecoveryLocation
		:public UASElement
	{
	public:
		KLVRangeToRecoveryLocation();
		virtual ~KLVRangeToRecoveryLocation();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTimeAirborne
	class KLVTimeAirborne
		:public UASElement
	{
	public:
		KLVTimeAirborne();
		virtual ~KLVTimeAirborne();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPropulsionUnitSpeed
	class KLVPropulsionUnitSpeed
		:public UASElement
	{
	public:
		KLVPropulsionUnitSpeed();
		virtual ~KLVPropulsionUnitSpeed();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformCourseAngle
	class KLVPlatformCourseAngle
		:public UASElement
	{
	public:
		KLVPlatformCourseAngle();
		virtual ~KLVPlatformCourseAngle();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAltitudeAGL
	class KLVAltitudeAGL
		:public UASElement
	{
	public:
		KLVAltitudeAGL();
		virtual ~KLVAltitudeAGL();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVRadarAltimeter
	class KLVRadarAltimeter
		:public UASElement
	{
	public:
		KLVRadarAltimeter();
		virtual ~KLVRadarAltimeter();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVControlCommand
	class KLVControlCommand
		:public UASElement
	{
	public:
		KLVControlCommand();
		virtual ~KLVControlCommand();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVControlCommandVerificationList
	class KLVControlCommandVerificationList
		:public UASElement
	{
	public:
		KLVControlCommandVerificationList();
		virtual ~KLVControlCommandVerificationList();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorAzimuthRate
	class KLVSensorAzimuthRate
		:public UASElement
	{
	public:
		KLVSensorAzimuthRate();
		virtual ~KLVSensorAzimuthRate();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorElevationRate
	class KLVSensorElevationRate
		:public UASElement
	{
	public:
		KLVSensorElevationRate();
		virtual ~KLVSensorElevationRate();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorRollRate
	class KLVSensorRollRate
		:public UASElement
	{
	public:
		KLVSensorRollRate();
		virtual ~KLVSensorRollRate();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOnboardMIStoragePercentFull
	class KLVOnboardMIStoragePercentFull
		:public UASElement
	{
	public:
		KLVOnboardMIStoragePercentFull();
		virtual ~KLVOnboardMIStoragePercentFull();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVActiveWavelengthList
	class KLVActiveWavelengthList
		:public UASElement
	{
	public:
		KLVActiveWavelengthList();
		virtual ~KLVActiveWavelengthList();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCountryCodes
	class KLVCountryCodes
		:public UASElement
	{
	public:
		KLVCountryCodes();
		virtual ~KLVCountryCodes();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVNumberofNAVSATsinView
	class KLVNumberofNAVSATsinView
		:public UASElement
	{
	public:
		KLVNumberofNAVSATsinView();
		virtual ~KLVNumberofNAVSATsinView();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPositioningMethodSource
	class KLVPositioningMethodSource
		:public UASElement
	{
	public:
		KLVPositioningMethodSource();
		virtual ~KLVPositioningMethodSource();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPlatformStatus
	class KLVPlatformStatus
		:public UASElement
	{
	public:
		KLVPlatformStatus();
		virtual ~KLVPlatformStatus();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorControlMode
	class KLVSensorControlMode
		:public UASElement
	{
	public:
		KLVSensorControlMode();
		virtual ~KLVSensorControlMode();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSensorFrameRatePack
	class KLVSensorFrameRatePack
		:public UASElement
	{
	public:
		KLVSensorFrameRatePack();
		virtual ~KLVSensorFrameRatePack();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWavelengthsList
	class KLVWavelengthsList
		:public UASElement
	{
	public:
		KLVWavelengthsList();
		virtual ~KLVWavelengthsList();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTargetID
	class KLVTargetID
		:public UASElement
	{
	public:
		KLVTargetID();
		virtual ~KLVTargetID();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVAirbaseLocations
	class KLVAirbaseLocations
		:public UASElement
	{
	public:
		KLVAirbaseLocations();
		virtual ~KLVAirbaseLocations();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTakeoffTime
	class KLVTakeoffTime
		:public UASElement
	{
	public:
		KLVTakeoffTime();
		virtual ~KLVTakeoffTime();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTransmissionFrequency
	class KLVTransmissionFrequency
		:public UASElement
	{
	public:
		KLVTransmissionFrequency();
		virtual ~KLVTransmissionFrequency();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVOnboardMIStorageCapacity
	class KLVOnboardMIStorageCapacity
		:public UASElement
	{
	public:
		KLVOnboardMIStorageCapacity();
		virtual ~KLVOnboardMIStorageCapacity();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVZoomPercentage
	class KLVZoomPercentage
		:public UASElement
	{
	public:
		KLVZoomPercentage();
		virtual ~KLVZoomPercentage();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCommunicationsMethod
	class KLVCommunicationsMethod
		:public UASElement
	{
	public:
		KLVCommunicationsMethod();
		virtual ~KLVCommunicationsMethod();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVLeapSeconds
	class KLVLeapSeconds
		:public UASElement
	{
	public:
		KLVLeapSeconds();
		virtual ~KLVLeapSeconds();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCorrectionOffset
	class KLVCorrectionOffset
		:public UASElement
	{
	public:
		KLVCorrectionOffset();
		virtual ~KLVCorrectionOffset();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVPayloadList
	class KLVPayloadList
		:public UASElement
	{
	public:
		KLVPayloadList();
		virtual ~KLVPayloadList();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVActivePayloads
	class KLVActivePayloads
		:public UASElement
	{
	public:
		KLVActivePayloads();
		virtual ~KLVActivePayloads();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWeaponsStores
	class KLVWeaponsStores
		:public UASElement
	{
	public:
		KLVWeaponsStores();
		virtual ~KLVWeaponsStores();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVWaypointList
	class KLVWaypointList
		:public UASElement
	{
	public:
		KLVWaypointList();
		virtual ~KLVWaypointList();
		LIBKLVP_DEFINE_VISITABLE(lcss::UASElement)
	};
}
#endif