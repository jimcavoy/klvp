#ifndef ENCODE_H
#define ENCODE_H

/// @file encode.h
///
/// KLVEncoder class definition

// klvlex generated on Thu Apr 02 10:25:01 2015

#include "klvelmt.h"
#include "klvelmtimpl.h"
#include "klvsselmtimpl.h"
#include <loki/Visitor.h>
#ifdef WIN32
#include <WinSock2.h>
#endif

namespace lcss
{
/// @brief Use KLVEncodeVisitor to take the machine datatypes (i.e int, double, char*) and KLV encode 
/// KLVElement instance's value field.  
class KLVEncodeVisitor
	: public Loki::BaseVisitor,
	public Loki::Visitor<lcss::KLVUnknown>,
	public Loki::Visitor<lcss::KLVParseError>,
	public Loki::Visitor<lcss::KLVChecksum>,
	public Loki::Visitor<lcss::KLVUNIXTimeStamp>,
	public Loki::Visitor<lcss::KLVMissionID>,
	public Loki::Visitor<lcss::KLVPlatformTailNumber>,
	public Loki::Visitor<lcss::KLVPlatformHeadingAngle>,
	public Loki::Visitor<lcss::KLVPlatformPitchAngle>,
	public Loki::Visitor<lcss::KLVPlatformRollAngle>,
	public Loki::Visitor<lcss::KLVPlatformTrueAirspeed>,
	public Loki::Visitor<lcss::KLVPlatformIndicatedAirspeed>,
	public Loki::Visitor<lcss::KLVPlatformDesignation>,
	public Loki::Visitor<lcss::KLVImageSourceSensor>,
	public Loki::Visitor<lcss::KLVImageCoordinateSystem>,
	public Loki::Visitor<lcss::KLVSensorLatitude>,
	public Loki::Visitor<lcss::KLVSensorLongitude>,
	public Loki::Visitor<lcss::KLVSensorTrueAltitude>,
	public Loki::Visitor<lcss::KLVSensorHorizontalFieldofView>,
	public Loki::Visitor<lcss::KLVSensorVerticalFieldofView>,
	public Loki::Visitor<lcss::KLVSensorRelativeAzimuthAngle>,
	public Loki::Visitor<lcss::KLVSensorRelativeElevationAngle>,
	public Loki::Visitor<lcss::KLVSensorRelativeRollAngle>,
	public Loki::Visitor<lcss::KLVSlantRange>,
	public Loki::Visitor<lcss::KLVTargetWidth>,
	public Loki::Visitor<lcss::KLVFrameCenterLatitude>,
	public Loki::Visitor<lcss::KLVFrameCenterLongitude>,
	public Loki::Visitor<lcss::KLVFrameCenterElevation>,
	public Loki::Visitor<lcss::KLVOffsetCornerLatitudePoint1>,
	public Loki::Visitor<lcss::KLVOffsetCornerLongitudePoint1>,
	public Loki::Visitor<lcss::KLVOffsetCornerLatitudePoint2>,
	public Loki::Visitor<lcss::KLVOffsetCornerLongitudePoint2>,
	public Loki::Visitor<lcss::KLVOffsetCornerLatitudePoint3>,
	public Loki::Visitor<lcss::KLVOffsetCornerLongitudePoint3>,
	public Loki::Visitor<lcss::KLVOffsetCornerLatitudePoint4>,
	public Loki::Visitor<lcss::KLVOffsetCornerLongitudePoint4>,
	public Loki::Visitor<lcss::KLVIcingDetected>,
	public Loki::Visitor<lcss::KLVWindDirection>,
	public Loki::Visitor<lcss::KLVWindSpeed>,
	public Loki::Visitor<lcss::KLVStaticPressure>,
	public Loki::Visitor<lcss::KLVDensityAltitude>,
	public Loki::Visitor<lcss::KLVOutsideAirTemperature>,
	public Loki::Visitor<lcss::KLVTargetLocationLatitude>,
	public Loki::Visitor<lcss::KLVTargetLocationLongitude>,
	public Loki::Visitor<lcss::KLVTargetLocationElevation>,
	public Loki::Visitor<lcss::KLVTargetTrackGateWidth>,
	public Loki::Visitor<lcss::KLVTargetTrackGateHeight>,
	public Loki::Visitor<lcss::KLVTargetErrorEstimateCE90>,
	public Loki::Visitor<lcss::KLVTargetErrorEstimateLE90>,
	public Loki::Visitor<lcss::KLVGenericFlagData01>,
	public Loki::Visitor<lcss::KLVSecurityLocalMetadataSet>,
	public Loki::Visitor<lcss::KLVDifferentialPressure>,
	public Loki::Visitor<lcss::KLVPlatformAngleofAttack>,
	public Loki::Visitor<lcss::KLVPlatformVerticalSpeed>,
	public Loki::Visitor<lcss::KLVPlatformSideslipAngle>,
	public Loki::Visitor<lcss::KLVAirfieldBarometicPressure>,
	public Loki::Visitor<lcss::KLVAirfieldElevation>,
	public Loki::Visitor<lcss::KLVRelativeHumidity>,
	public Loki::Visitor<lcss::KLVPlatformGroundSpeed>,
	public Loki::Visitor<lcss::KLVGroundRange>,
	public Loki::Visitor<lcss::KLVPlatformFuelRemaining>,
	public Loki::Visitor<lcss::KLVPlatformCallSign>,
	public Loki::Visitor<lcss::KLVWeaponLoad>,
	public Loki::Visitor<lcss::KLVWeaponFired>,
	public Loki::Visitor<lcss::KLVLaserPRFCode>,
	public Loki::Visitor<lcss::KLVSensorFieldofViewName>,
	public Loki::Visitor<lcss::KLVPlatformMagneticHeading>,
	public Loki::Visitor<lcss::KLVUASLDSVersionNumber>,
	public Loki::Visitor<lcss::KLVTargetLocationCovarianceMatrix>,
	public Loki::Visitor<lcss::KLVAlternatePlatformLatitude>,
	public Loki::Visitor<lcss::KLVAlternatePlatformLongitude>,
	public Loki::Visitor<lcss::KLVAlternatePlatformAltitude>,
	public Loki::Visitor<lcss::KLVAlternatePlatformName>,
	public Loki::Visitor<lcss::KLVAlternatePlatformHeading>,
	public Loki::Visitor<lcss::KLVEventStartTimeUTC>,
	public Loki::Visitor<lcss::KLVRVTLocalDataSet>,
	public Loki::Visitor<lcss::KLVVMTILocalDataSet>,
	public Loki::Visitor<lcss::KLVSensorEllipsoidHeight>,
	public Loki::Visitor<lcss::KLVAlternatePlatformEllipsoidHeight>,
	public Loki::Visitor<lcss::KLVOperationalMode>,
	public Loki::Visitor<lcss::KLVFrameCenterHeightAboveEllipsoid>,
	public Loki::Visitor<lcss::KLVSensorNorthVelocity>,
	public Loki::Visitor<lcss::KLVSensorEastVelocity>,
	public Loki::Visitor<lcss::KLVImageHorizonPixelPack>,
	public Loki::Visitor<lcss::KLVCornerLatitudePoint1Full>,
	public Loki::Visitor<lcss::KLVCornerLongitudePoint1Full>,
	public Loki::Visitor<lcss::KLVCornerLatitudePoint2Full>,
	public Loki::Visitor<lcss::KLVCornerLongitudePoint2Full>,
	public Loki::Visitor<lcss::KLVCornerLatitudePoint3Full>,
	public Loki::Visitor<lcss::KLVCornerLongitudePoint3Full>,
	public Loki::Visitor<lcss::KLVCornerLatitudePoint4Full>,
	public Loki::Visitor<lcss::KLVCornerLongitudePoint4Full>,
	public Loki::Visitor<lcss::KLVPlatformPitchAngleFull>,
	public Loki::Visitor<lcss::KLVPlatformRollAngleFull>,
	public Loki::Visitor<lcss::KLVPlatformAngleofAttackFull>,
	public Loki::Visitor<lcss::KLVPlatformSideslipAngleFull>,
	public Loki::Visitor<lcss::KLVMIISCoreIdentifier>, 
	public Loki::Visitor<lcss::KLVSARMotionImageryMetadata>,
	public Loki::Visitor<lcss::KLVTargetWidthExtended>,
	public Loki::Visitor<lcss::KLVRangeImageLocalSet>,
	public Loki::Visitor<lcss::KLVGeoRegistrationLocalSet>,
	public Loki::Visitor<lcss::KLVCompositeImagingLocalSet>,
	public Loki::Visitor<lcss::KLVSegmentLocalSet>,
	public Loki::Visitor<lcss::KLVAmendLocalSet>,
	public Loki::Visitor<lcss::KLVSDCCFLP>,
	public Loki::Visitor<lcss::KLVDensityAltitudeExtended>,
	public Loki::Visitor<lcss::KLVSensorEllipsoidHeightExtended>,
	public Loki::Visitor<lcss::KLVAlternatePlatformEllipsoidHeightExtended>,
	public Loki::Visitor<lcss::KLVStreamDesignator>,
	public Loki::Visitor<lcss::KLVOperationalBase>,
	public Loki::Visitor<lcss::KLVBroadcastSource>,
	public Loki::Visitor<lcss::KLVRangeToRecoveryLocation>,
	public Loki::Visitor<lcss::KLVTimeAirborne>,
	public Loki::Visitor<lcss::KLVPropulsionUnitSpeed>,
	public Loki::Visitor<lcss::KLVPlatformCourseAngle>,
	public Loki::Visitor<lcss::KLVAltitudeAGL>,
	public Loki::Visitor<lcss::KLVRadarAltimeter>,
	public Loki::Visitor<lcss::KLVControlCommand>,
	public Loki::Visitor<lcss::KLVControlCommandVerificationList>,
	public Loki::Visitor<lcss::KLVSensorAzimuthRate>,
	public Loki::Visitor<lcss::KLVSensorElevationRate>,
	public Loki::Visitor<lcss::KLVSensorRollRate>,
	public Loki::Visitor<lcss::KLVOnboardMIStoragePercentFull>,
	public Loki::Visitor<lcss::KLVActiveWavelengthList>,
	public Loki::Visitor<lcss::KLVCountryCodes>,
	public Loki::Visitor<lcss::KLVNumberofNAVSATsinView>,
	public Loki::Visitor<lcss::KLVPositioningMethodSource>,
	public Loki::Visitor<lcss::KLVPlatformStatus>,
	public Loki::Visitor<lcss::KLVSensorControlMode>,
	public Loki::Visitor<lcss::KLVSensorFrameRatePack>,
	public Loki::Visitor<lcss::KLVWavelengthsList>,
	public Loki::Visitor<lcss::KLVTargetID>,
	public Loki::Visitor<lcss::KLVAirbaseLocations>,
	public Loki::Visitor<lcss::KLVTakeoffTime>,
	public Loki::Visitor<lcss::KLVTransmissionFrequency>,
	public Loki::Visitor<lcss::KLVOnboardMIStorageCapacity>,
	public Loki::Visitor<lcss::KLVZoomPercentage>,
	public Loki::Visitor<lcss::KLVCommunicationsMethod>,
	public Loki::Visitor<lcss::KLVLeapSeconds>,
	public Loki::Visitor<lcss::KLVCorrectionOffset>,
	public Loki::Visitor<lcss::KLVPayloadList>,
	public Loki::Visitor<lcss::KLVActivePayloads>,
	public Loki::Visitor<lcss::KLVWeaponsStores>,
	public Loki::Visitor<lcss::KLVWaypointList>,
	public Loki::Visitor<lcss::KLVObjectCountryCodingMethodVersionDate>,
	public Loki::Visitor<lcss::KLVSecurityClassification>,
	public Loki::Visitor<lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod>,
	public Loki::Visitor<lcss::KLVClassifyingCountry>,
	public Loki::Visitor<lcss::KLVSecuritySCISHIinformation>,
	public Loki::Visitor<lcss::KLVCaveats>,
	public Loki::Visitor<lcss::KLVReleasingInstructions>,
	public Loki::Visitor<lcss::KLVClassifiedBy>,
	public Loki::Visitor<lcss::KLVDerivedFrom>,
	public Loki::Visitor<lcss::KLVClassificationReason>,
	public Loki::Visitor<lcss::KLVDeclassificationDate>,
	public Loki::Visitor<lcss::KLVClassificationandMarkingSystem>,
	public Loki::Visitor<lcss::KLVObjectCountryCodingMethod>,
	public Loki::Visitor<lcss::KLVObjectCountryCodes>,
	public Loki::Visitor<lcss::KLVClassificationComments>,
	public Loki::Visitor<lcss::KLVUMIDVideo>,
	public Loki::Visitor<lcss::KLVUMIDAudio>,
	public Loki::Visitor<lcss::KLVUMIDData>,
	public Loki::Visitor<lcss::KLVUMIDSystem>,
	public Loki::Visitor<lcss::KLVStreamID>,
	public Loki::Visitor<lcss::KLVTransportStreamID>,
	public Loki::Visitor<lcss::KLVItemDesignator>,
	public Loki::Visitor<lcss::KLVVersion>,
	public Loki::Visitor<lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate>
{
public:
	KLVEncodeVisitor();

	void Visit(lcss::KLVUnknown& klv);
	void Visit(lcss::KLVParseError& klv);
	void Visit(lcss::KLVChecksum& klv);
	void Visit(lcss::KLVUNIXTimeStamp& klv);
	void Visit(lcss::KLVMissionID& klv);
	void Visit(lcss::KLVPlatformTailNumber& klv);
	void Visit(lcss::KLVPlatformHeadingAngle& klv);
	void Visit(lcss::KLVPlatformPitchAngle& klv);
	void Visit(lcss::KLVPlatformRollAngle& klv);
	void Visit(lcss::KLVPlatformTrueAirspeed& klv);
	void Visit(lcss::KLVPlatformIndicatedAirspeed& klv);
	void Visit(lcss::KLVPlatformDesignation& klv);
	void Visit(lcss::KLVImageSourceSensor& klv);
	void Visit(lcss::KLVImageCoordinateSystem& klv);
	void Visit(lcss::KLVSensorLatitude& klv);
	void Visit(lcss::KLVSensorLongitude& klv);
	void Visit(lcss::KLVSensorTrueAltitude& klv);
	void Visit(lcss::KLVSensorHorizontalFieldofView& klv);
	void Visit(lcss::KLVSensorVerticalFieldofView& klv);
	void Visit(lcss::KLVSensorRelativeAzimuthAngle& klv);
	void Visit(lcss::KLVSensorRelativeElevationAngle& klv);
	void Visit(lcss::KLVSensorRelativeRollAngle& klv);
	void Visit(lcss::KLVSlantRange& klv);
	void Visit(lcss::KLVTargetWidth& klv);
	void Visit(lcss::KLVFrameCenterLatitude& klv);
	void Visit(lcss::KLVFrameCenterLongitude& klv);
	void Visit(lcss::KLVFrameCenterElevation& klv);
	void Visit(lcss::KLVOffsetCornerLatitudePoint1& klv);
	void Visit(lcss::KLVOffsetCornerLongitudePoint1& klv);
	void Visit(lcss::KLVOffsetCornerLatitudePoint2& klv);
	void Visit(lcss::KLVOffsetCornerLongitudePoint2& klv);
	void Visit(lcss::KLVOffsetCornerLatitudePoint3& klv);
	void Visit(lcss::KLVOffsetCornerLongitudePoint3& klv);
	void Visit(lcss::KLVOffsetCornerLatitudePoint4& klv);
	void Visit(lcss::KLVOffsetCornerLongitudePoint4& klv);
	void Visit(lcss::KLVIcingDetected& klv);
	void Visit(lcss::KLVWindDirection& klv);
	void Visit(lcss::KLVWindSpeed& klv);
	void Visit(lcss::KLVStaticPressure& klv);
	void Visit(lcss::KLVDensityAltitude& klv);
	void Visit(lcss::KLVOutsideAirTemperature& klv);
	void Visit(lcss::KLVTargetLocationLatitude& klv);
	void Visit(lcss::KLVTargetLocationLongitude& klv);
	void Visit(lcss::KLVTargetLocationElevation& klv);
	void Visit(lcss::KLVTargetTrackGateWidth& klv);
	void Visit(lcss::KLVTargetTrackGateHeight& klv);
	void Visit(lcss::KLVTargetErrorEstimateCE90& klv);
	void Visit(lcss::KLVTargetErrorEstimateLE90& klv);
	void Visit(lcss::KLVGenericFlagData01& klv);
	void Visit(lcss::KLVSecurityLocalMetadataSet& klv);
	void Visit(lcss::KLVDifferentialPressure& klv);
	void Visit(lcss::KLVPlatformAngleofAttack& klv);
	void Visit(lcss::KLVPlatformVerticalSpeed& klv);
	void Visit(lcss::KLVPlatformSideslipAngle& klv);
	void Visit(lcss::KLVAirfieldBarometicPressure& klv);
	void Visit(lcss::KLVAirfieldElevation& klv);
	void Visit(lcss::KLVRelativeHumidity& klv);
	void Visit(lcss::KLVPlatformGroundSpeed& klv);
	void Visit(lcss::KLVGroundRange& klv);
	void Visit(lcss::KLVPlatformFuelRemaining& klv);
	void Visit(lcss::KLVPlatformCallSign& klv);
	void Visit(lcss::KLVWeaponLoad& klv);
	void Visit(lcss::KLVWeaponFired& klv);
	void Visit(lcss::KLVLaserPRFCode& klv);
	void Visit(lcss::KLVSensorFieldofViewName& klv);
	void Visit(lcss::KLVPlatformMagneticHeading& klv);
	void Visit(lcss::KLVUASLDSVersionNumber& klv);
	void Visit(lcss::KLVTargetLocationCovarianceMatrix& klv);
	void Visit(lcss::KLVAlternatePlatformLatitude& klv);
	void Visit(lcss::KLVAlternatePlatformLongitude& klv);
	void Visit(lcss::KLVAlternatePlatformAltitude& klv);
	void Visit(lcss::KLVAlternatePlatformName& klv);
	void Visit(lcss::KLVAlternatePlatformHeading& klv);
	void Visit(lcss::KLVEventStartTimeUTC& klv);
	void Visit(lcss::KLVRVTLocalDataSet& klv);
	void Visit(lcss::KLVVMTILocalDataSet& klv);
	void Visit(lcss::KLVSensorEllipsoidHeight& klv);
	void Visit(lcss::KLVAlternatePlatformEllipsoidHeight& klv);
	void Visit(lcss::KLVOperationalMode& klv);
	void Visit(lcss::KLVFrameCenterHeightAboveEllipsoid& klv);
	void Visit(lcss::KLVSensorNorthVelocity& klv);
	void Visit(lcss::KLVSensorEastVelocity& klv);
	void Visit(lcss::KLVImageHorizonPixelPack& klv);
	void Visit(lcss::KLVCornerLatitudePoint1Full& klv);
	void Visit(lcss::KLVCornerLongitudePoint1Full& klv);
	void Visit(lcss::KLVCornerLatitudePoint2Full& klv);
	void Visit(lcss::KLVCornerLongitudePoint2Full& klv);
	void Visit(lcss::KLVCornerLatitudePoint3Full& klv);
	void Visit(lcss::KLVCornerLongitudePoint3Full& klv);
	void Visit(lcss::KLVCornerLatitudePoint4Full& klv);
	void Visit(lcss::KLVCornerLongitudePoint4Full& klv);
	void Visit(lcss::KLVPlatformPitchAngleFull& klv);
	void Visit(lcss::KLVPlatformRollAngleFull& klv);
	void Visit(lcss::KLVPlatformAngleofAttackFull& klv);
	void Visit(lcss::KLVPlatformSideslipAngleFull& klv);
	void Visit(lcss::KLVMIISCoreIdentifier& klv);
	void Visit(lcss::KLVSARMotionImageryMetadata& klv);
	void Visit(lcss::KLVTargetWidthExtended& klv);
	void Visit(lcss::KLVRangeImageLocalSet& klv);
	void Visit(lcss::KLVGeoRegistrationLocalSet& klv);
	void Visit(lcss::KLVCompositeImagingLocalSet& klv);
	void Visit(lcss::KLVSegmentLocalSet& klv);
	void Visit(lcss::KLVAmendLocalSet& klv);
	void Visit(lcss::KLVSDCCFLP& klv);
	void Visit(lcss::KLVDensityAltitudeExtended& klv);
	void Visit(lcss::KLVSensorEllipsoidHeightExtended& klv);
	void Visit(lcss::KLVAlternatePlatformEllipsoidHeightExtended& klv);
	void Visit(lcss::KLVStreamDesignator& klv);
	void Visit(lcss::KLVOperationalBase& klv);
	void Visit(lcss::KLVBroadcastSource& klv);
	void Visit(lcss::KLVRangeToRecoveryLocation& klv);
	void Visit(lcss::KLVTimeAirborne& klv);
	void Visit(lcss::KLVPropulsionUnitSpeed& klv);
	void Visit(lcss::KLVPlatformCourseAngle& klv);
	void Visit(lcss::KLVAltitudeAGL& klv);
	void Visit(lcss::KLVRadarAltimeter& klv);
	void Visit(lcss::KLVControlCommand& klv);
	void Visit(lcss::KLVControlCommandVerificationList& klv);
	void Visit(lcss::KLVSensorAzimuthRate& klv);
	void Visit(lcss::KLVSensorElevationRate& klv);
	void Visit(lcss::KLVSensorRollRate& klv);
	void Visit(lcss::KLVOnboardMIStoragePercentFull& klv);
	void Visit(lcss::KLVActiveWavelengthList& klv);
	void Visit(lcss::KLVCountryCodes& klv);
	void Visit(lcss::KLVNumberofNAVSATsinView& klv);
	void Visit(lcss::KLVPositioningMethodSource& klv);
	void Visit(lcss::KLVPlatformStatus& klv);
	void Visit(lcss::KLVSensorControlMode& klv);
	void Visit(lcss::KLVSensorFrameRatePack& klv);
	void Visit(lcss::KLVWavelengthsList& klv);
	void Visit(lcss::KLVTargetID& klv);
	void Visit(lcss::KLVAirbaseLocations& klv);
	void Visit(lcss::KLVTakeoffTime& klv);
	void Visit(lcss::KLVTransmissionFrequency& klv);
	void Visit(lcss::KLVOnboardMIStorageCapacity& klv);
	void Visit(lcss::KLVZoomPercentage& klv);
	void Visit(lcss::KLVCommunicationsMethod& klv);
	void Visit(lcss::KLVLeapSeconds& klv);
	void Visit(lcss::KLVCorrectionOffset& klv);
	void Visit(lcss::KLVPayloadList& klv);
	void Visit(lcss::KLVActivePayloads& klv);
	void Visit(lcss::KLVWeaponsStores& klv);
	void Visit(lcss::KLVWaypointList& klv);

	// Security Set KLV Elements
	void Visit(lcss::KLVObjectCountryCodingMethodVersionDate& klv);
	void Visit(lcss::KLVSecurityClassification& klv);
	void Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod& klv);
	void Visit(lcss::KLVClassifyingCountry& klv);
	void Visit(lcss::KLVSecuritySCISHIinformation& klv);
	void Visit(lcss::KLVCaveats& klv);
	void Visit(lcss::KLVReleasingInstructions& klv);
	void Visit(lcss::KLVClassifiedBy& klv);
	void Visit(lcss::KLVDerivedFrom& klv);
	void Visit(lcss::KLVClassificationReason& klv);
	void Visit(lcss::KLVDeclassificationDate& klv);
	void Visit(lcss::KLVClassificationandMarkingSystem& klv);
	void Visit(lcss::KLVObjectCountryCodingMethod& klv);
	void Visit(lcss::KLVObjectCountryCodes& klv);
	void Visit(lcss::KLVClassificationComments& klv);
	void Visit(lcss::KLVUMIDVideo& klv);
	void Visit(lcss::KLVUMIDAudio& klv);
	void Visit(lcss::KLVUMIDData& klv);
	void Visit(lcss::KLVUMIDSystem& klv);
	void Visit(lcss::KLVStreamID& klv);
	void Visit(lcss::KLVTransportStreamID& klv);
	void Visit(lcss::KLVItemDesignator& klv);
	void Visit(lcss::KLVVersion& klv);
	void Visit(lcss::KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate& klv);

public:
	timeval		timestamp;
	double		dblValue;
	int			nValue;
	std::string	strValue;
	double		frameCenterLatLon;

private:
	uint8_t value[8]{};
};

}
#endif