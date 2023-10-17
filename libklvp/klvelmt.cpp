#include "klvelmt.h"

#include "klvelmtimpl.h"
#include "klvuselmtimpl.h"


lcss::KLVElement::KLVElement()
{

}

lcss::KLVElement::KLVElement(uint8_t key)
{
	switch (key)
	{
	case 0x01: pimpl_ = std::make_shared<lcss::KLVChecksum>(); break;
	case 0x02: pimpl_ = std::make_shared<lcss::KLVUNIXTimeStamp>(); break;
	case 0x03: pimpl_ = std::make_shared<lcss::KLVMissionID>(); break;
	case 0x04: pimpl_ = std::make_shared<lcss::KLVPlatformTailNumber>(); break;
	case 0x05: pimpl_ = std::make_shared<lcss::KLVPlatformHeadingAngle>(); break;
	case 0x06: pimpl_ = std::make_shared<lcss::KLVPlatformPitchAngle>(); break;
	case 0x07: pimpl_ = std::make_shared<lcss::KLVPlatformRollAngle>(); break;
	case 0x08: pimpl_ = std::make_shared<lcss::KLVPlatformTrueAirspeed>(); break;
	case 0x09: pimpl_ = std::make_shared<lcss::KLVPlatformIndicatedAirspeed>(); break;
	case 0x0A: pimpl_ = std::make_shared<lcss::KLVPlatformDesignation>(); break;
	case 0x0B: pimpl_ = std::make_shared<lcss::KLVImageSourceSensor>(); break;
	case 0x0C: pimpl_ = std::make_shared<lcss::KLVImageCoordinateSystem>(); break;
	case 0x0D: pimpl_ = std::make_shared<lcss::KLVSensorLatitude>(); break;
	case 0x0E: pimpl_ = std::make_shared<lcss::KLVSensorLongitude>(); break;
	case 0x0F: pimpl_ = std::make_shared<lcss::KLVSensorTrueAltitude>(); break;
	case 0x10: pimpl_ = std::make_shared<lcss::KLVSensorHorizontalFieldofView>(); break;
	case 0x11: pimpl_ = std::make_shared<lcss::KLVSensorVerticalFieldofView>(); break;
	case 0x12: pimpl_ = std::make_shared<lcss::KLVSensorRelativeAzimuthAngle>(); break;
	case 0x13: pimpl_ = std::make_shared<lcss::KLVSensorRelativeElevationAngle>(); break;
	case 0x14: pimpl_ = std::make_shared<lcss::KLVSensorRelativeRollAngle>(); break;
	case 0x15: pimpl_ = std::make_shared<lcss::KLVSlantRange>(); break;
	case 0x16: pimpl_ = std::make_shared<lcss::KLVTargetWidth>(); break;
	case 0x17: pimpl_ = std::make_shared<lcss::KLVFrameCenterLatitude>(); break;
	case 0x18: pimpl_ = std::make_shared<lcss::KLVFrameCenterLongitude>(); break;
	case 0x19: pimpl_ = std::make_shared<lcss::KLVFrameCenterElevation>(); break;
	case 0x1A: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLatitudePoint1>(); break;
	case 0x1B: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLongitudePoint1>(); break;
	case 0x1C: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLatitudePoint2>(); break;
	case 0x1D: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLongitudePoint2>(); break;
	case 0x1E: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLatitudePoint3>(); break;
	case 0x1F: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLongitudePoint3>(); break;
	case 0x20: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLatitudePoint4>(); break;
	case 0x21: pimpl_ = std::make_shared<lcss::KLVOffsetCornerLongitudePoint4>(); break;
	case 0x22: pimpl_ = std::make_shared<lcss::KLVIcingDetected>(); break;
	case 0x23: pimpl_ = std::make_shared<lcss::KLVWindDirection>(); break;
	case 0x24: pimpl_ = std::make_shared<lcss::KLVWindSpeed>(); break;
	case 0x25: pimpl_ = std::make_shared<lcss::KLVStaticPressure>(); break;
	case 0x26: pimpl_ = std::make_shared<lcss::KLVDensityAltitude>(); break;
	case 0x27: pimpl_ = std::make_shared<lcss::KLVOutsideAirTemperature>(); break;
	case 0x28: pimpl_ = std::make_shared<lcss::KLVTargetLocationLatitude>(); break;
	case 0x29: pimpl_ = std::make_shared<lcss::KLVTargetLocationLongitude>(); break;
	case 0x2A: pimpl_ = std::make_shared<lcss::KLVTargetLocationElevation>(); break;
	case 0x2B: pimpl_ = std::make_shared<lcss::KLVTargetTrackGateWidth>(); break;
	case 0x2C: pimpl_ = std::make_shared<lcss::KLVTargetTrackGateHeight>(); break;
	case 0x2D: pimpl_ = std::make_shared<lcss::KLVTargetErrorEstimateCE90>(); break;
	case 0x2E: pimpl_ = std::make_shared<lcss::KLVTargetErrorEstimateLE90>(); break;
	case 0x2F: pimpl_ = std::make_shared<lcss::KLVGenericFlagData01>(); break;
	case 0x30: pimpl_ = std::make_shared<lcss::KLVSecurityLocalMetadataSet>(); break;
	case 0x31: pimpl_ = std::make_shared<lcss::KLVDifferentialPressure>(); break;
	case 0x32: pimpl_ = std::make_shared<lcss::KLVPlatformAngleofAttack>(); break;
	case 0x33: pimpl_ = std::make_shared<lcss::KLVPlatformVerticalSpeed>(); break;
	case 0x34: pimpl_ = std::make_shared<lcss::KLVPlatformSideslipAngle>(); break;
	case 0x35: pimpl_ = std::make_shared<lcss::KLVAirfieldBarometicPressure>(); break;
	case 0x36: pimpl_ = std::make_shared<lcss::KLVAirfieldElevation>(); break;
	case 0x37: pimpl_ = std::make_shared<lcss::KLVRelativeHumidity>(); break;
	case 0x38: pimpl_ = std::make_shared<lcss::KLVPlatformGroundSpeed>(); break;
	case 0x39: pimpl_ = std::make_shared<lcss::KLVGroundRange>(); break;
	case 0x3A: pimpl_ = std::make_shared<lcss::KLVPlatformFuelRemaining>(); break;
	case 0x3B: pimpl_ = std::make_shared<lcss::KLVPlatformCallSign>(); break;
	case 0x3C: pimpl_ = std::make_shared<lcss::KLVWeaponLoad>(); break;
	case 0x3D: pimpl_ = std::make_shared<lcss::KLVWeaponFired>(); break;
	case 0x3E: pimpl_ = std::make_shared<lcss::KLVLaserPRFCode>(); break;
	case 0x3F: pimpl_ = std::make_shared<lcss::KLVSensorFieldofViewName>(); break;
	case 0x40: pimpl_ = std::make_shared<lcss::KLVPlatformMagneticHeading>(); break;
	case 0x41: pimpl_ = std::make_shared<lcss::KLVUASLDSVersionNumber>(); break;
	case 0x42: pimpl_ = std::make_shared<lcss::KLVTargetLocationCovarianceMatrix>(); break;
	case 0x43: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformLatitude>(); break;
	case 0x44: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformLongitude>(); break;
	case 0x45: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformAltitude>(); break;
	case 0x46: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformName>(); break;
	case 0x47: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformHeading>(); break;
	case 0x48: pimpl_ = std::make_shared<lcss::KLVEventStartTimeUTC>(); break;
	case 0x49: pimpl_ = std::make_shared<lcss::KLVRVTLocalDataSet>(); break;
	case 0x4A: pimpl_ = std::make_shared<lcss::KLVVMTILocalDataSet>(); break;
	case 0x4B: pimpl_ = std::make_shared<lcss::KLVSensorEllipsoidHeight>(); break;
	case 0x4C: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformEllipsoidHeight>(); break;
	case 0x4D: pimpl_ = std::make_shared<lcss::KLVOperationalMode>(); break;
	case 0x4E: pimpl_ = std::make_shared<lcss::KLVFrameCenterHeightAboveEllipsoid>(); break;
	case 0x4F: pimpl_ = std::make_shared<lcss::KLVSensorNorthVelocity>(); break;
	case 0x50: pimpl_ = std::make_shared<lcss::KLVSensorEastVelocity>(); break;
	case 0x51: pimpl_ = std::make_shared<lcss::KLVImageHorizonPixelPack>(); break;
	case 0x52: pimpl_ = std::make_shared<lcss::KLVCornerLatitudePoint1Full>(); break;
	case 0x53: pimpl_ = std::make_shared<lcss::KLVCornerLongitudePoint1Full>(); break;
	case 0x54: pimpl_ = std::make_shared<lcss::KLVCornerLatitudePoint2Full>(); break;
	case 0x55: pimpl_ = std::make_shared<lcss::KLVCornerLongitudePoint2Full>(); break;
	case 0x56: pimpl_ = std::make_shared<lcss::KLVCornerLatitudePoint3Full>(); break;
	case 0x57: pimpl_ = std::make_shared<lcss::KLVCornerLongitudePoint3Full>(); break;
	case 0x58: pimpl_ = std::make_shared<lcss::KLVCornerLatitudePoint4Full>(); break;
	case 0x59: pimpl_ = std::make_shared<lcss::KLVCornerLongitudePoint4Full>(); break;
	case 0x5A: pimpl_ = std::make_shared<lcss::KLVPlatformPitchAngleFull>(); break;
	case 0x5B: pimpl_ = std::make_shared<lcss::KLVPlatformRollAngleFull>(); break;
	case 0x5C: pimpl_ = std::make_shared<lcss::KLVPlatformAngleofAttackFull>(); break;
	case 0x5D: pimpl_ = std::make_shared<lcss::KLVPlatformSideslipAngleFull>(); break;
	case 0x5E: pimpl_ = std::make_shared<lcss::KLVMIISCoreIdentifier>(); break;
	case 0x5F: pimpl_ = std::make_shared<lcss::KLVSARMotionImageryMetadata>(); break;
	case 0x60: pimpl_ = std::make_shared<lcss::KLVTargetWidthExtended>(); break;
	case 0x61: pimpl_ = std::make_shared<lcss::KLVRangeImageLocalSet>(); break;
	case 0x62: pimpl_ = std::make_shared<lcss::KLVGeoRegistrationLocalSet>(); break;
	case 0x63: pimpl_ = std::make_shared<lcss::KLVCompositeImagingLocalSet>(); break;
	case 0x64: pimpl_ = std::make_shared<lcss::KLVSegmentLocalSet>(); break;
	case 0x65: pimpl_ = std::make_shared<lcss::KLVAmendLocalSet>(); break;
	case 0x66: pimpl_ = std::make_shared<lcss::KLVSDCCFLP>(); break;
	case 0x67: pimpl_ = std::make_shared<lcss::KLVDensityAltitudeExtended>(); break;
	case 0x68: pimpl_ = std::make_shared<lcss::KLVSensorEllipsoidHeightExtended>(); break;
	case 0x69: pimpl_ = std::make_shared<lcss::KLVAlternatePlatformEllipsoidHeightExtended>(); break;
	case 0x6A: pimpl_ = std::make_shared<lcss::KLVStreamDesignator>(); break;
	case 0x6B: pimpl_ = std::make_shared<lcss::KLVOperationalBase>(); break;
	case 0x6C: pimpl_ = std::make_shared<lcss::KLVBroadcastSource>(); break;
	case 0x6D: pimpl_ = std::make_shared<lcss::KLVRangeToRecoveryLocation>(); break;
	case 0x6E: pimpl_ = std::make_shared<lcss::KLVTimeAirborne>(); break;
	case 0x6F: pimpl_ = std::make_shared<lcss::KLVPropulsionUnitSpeed>(); break;
	case 0x70: pimpl_ = std::make_shared<lcss::KLVPlatformCourseAngle>(); break;
	case 0x71: pimpl_ = std::make_shared<lcss::KLVAltitudeAGL>(); break;
	case 0x72: pimpl_ = std::make_shared<lcss::KLVRadarAltimeter>(); break;
	case 0x73: pimpl_ = std::make_shared<lcss::KLVControlCommand>(); break;
	case 0x74: pimpl_ = std::make_shared<lcss::KLVControlCommandVerificationList>(); break;
	case 0x75: pimpl_ = std::make_shared<lcss::KLVSensorAzimuthRate>(); break;
	case 0x76: pimpl_ = std::make_shared<lcss::KLVSensorElevationRate>(); break;
	case 0x77: pimpl_ = std::make_shared<lcss::KLVSensorRollRate>(); break;
	case 0x78: pimpl_ = std::make_shared<lcss::KLVOnboardMIStoragePercentFull>(); break;
	case 0x79: pimpl_ = std::make_shared<lcss::KLVActiveWavelengthList>(); break;
	case 0x7A: pimpl_ = std::make_shared<lcss::KLVCountryCodes>(); break;
	case 0x7B: pimpl_ = std::make_shared<lcss::KLVNumberofNAVSATsinView>(); break;
	case 0x7C: pimpl_ = std::make_shared<lcss::KLVPositioningMethodSource>(); break;
	case 0x7D: pimpl_ = std::make_shared<lcss::KLVPlatformStatus>(); break;
	case 0x7E: pimpl_ = std::make_shared<lcss::KLVSensorControlMode>(); break;
	case 0x7F: pimpl_ = std::make_shared<lcss::KLVSensorFrameRatePack>(); break;
	case 0x80: pimpl_ = std::make_shared<lcss::KLVWavelengthsList>(); break;
	case 0x81: pimpl_ = std::make_shared<lcss::KLVTargetID>(); break;
	case 0x82: pimpl_ = std::make_shared<lcss::KLVAirbaseLocations>(); break;
	case 0x83: pimpl_ = std::make_shared<lcss::KLVTakeoffTime>(); break;
	case 0x84: pimpl_ = std::make_shared<lcss::KLVTransmissionFrequency>(); break;
	case 0x85: pimpl_ = std::make_shared<lcss::KLVOnboardMIStorageCapacity>(); break;
	case 0x86: pimpl_ = std::make_shared<lcss::KLVZoomPercentage>(); break;
	case 0x87: pimpl_ = std::make_shared<lcss::KLVCommunicationsMethod>(); break;
	case 0x88: pimpl_ = std::make_shared<lcss::KLVLeapSeconds>(); break;
	case 0x89: pimpl_ = std::make_shared<lcss::KLVCorrectionOffset>(); break;
	case 0x8A: pimpl_ = std::make_shared<lcss::KLVPayloadList>(); break;
	case 0x8B: pimpl_ = std::make_shared<lcss::KLVActivePayloads>(); break;
	case 0x8C: pimpl_ = std::make_shared<lcss::KLVWeaponsStores>(); break;
	case 0x8D: pimpl_ = std::make_shared<lcss::KLVWaypointList>(); break;
	default:
		pimpl_ = std::make_shared<lcss::KLVUnknown>(key);
	}
}

lcss::KLVElement::KLVElement(const uint8_t* key, int size)
{
	uint8_t bKey[16]{};
	for (int i = 0; i < size; i++)
	{
		if (i < 16) // prevent overflow
			bKey[i] = key[i];
	}
	pimpl_ = std::make_shared<lcss::UniversalMetadataElement>(bKey);
}

lcss::KLVElement::~KLVElement()
{

}

lcss::KLVElement::KLVElement(const KLVElement& orig)
{
	KLVElement& temp = const_cast<KLVElement&>(orig);
	pimpl_ = temp.pimpl_;
}

lcss::KLVElement::KLVElement(KLVElement&& src) noexcept
{
	// Eliminate redundant code by writing the move constructor to call the
	// move assignment operator.
	pimpl_ = std::move(src.pimpl_);
}

lcss::KLVElement& lcss::KLVElement::operator=(const lcss::KLVElement& rhs)
{
	KLVElement temp(rhs);
	swap(temp);
	return *this;
}

lcss::KLVElement& lcss::KLVElement::operator=(lcss::KLVElement&& rhs) noexcept
{
	if (this != &rhs)
	{
		pimpl_ = std::move(rhs.pimpl_);
	}
	return *this;
}

void lcss::KLVElement::swap(lcss::KLVElement& src)
{
	std::swap(pimpl_, src.pimpl_);
}

uint8_t lcss::KLVElement::key() const
{
	if (pimpl_.get() != nullptr)
		return pimpl_->key();
	return 0;
}


int lcss::KLVElement::key(uint8_t* keybuf) const
{
	if (pimpl_.get() != nullptr)
		return pimpl_->key(keybuf);
	return 0;
}


int lcss::KLVElement::length() const
{
	if (pimpl_.get() != nullptr)
		return pimpl_->length();
	return 0;
}

int lcss::KLVElement::numOfBytesForLength() const
{
	if (pimpl_.get() != nullptr)
	{
		pimpl_->numOfBytesForLength();
	}
	return 0;
}

void lcss::KLVElement::value(uint8_t* buf) const
{
	if (pimpl_.get() != nullptr)
		pimpl_->value(buf);
}

uint8_t* lcss::KLVElement::value()
{
	if (pimpl_.get() != nullptr)
		return pimpl_->value();
	return nullptr;
}

void lcss::KLVElement::setValue(uint8_t* buf, int bufsz)
{
	if (pimpl_.get() != nullptr)
		pimpl_->setValue(buf, bufsz);
}

int lcss::KLVElement::serialize(uint8_t* buf, int bufsz)
{
	if (pimpl_.get() != nullptr)
		return pimpl_->serialize(buf, bufsz);
	return 0;
}

void* lcss::KLVElement::appData()
{
	if (pimpl_.get() != nullptr)
		return pimpl_->appData();
	return nullptr;
}

void lcss::KLVElement::setAppData(void* appData)
{
	if (pimpl_.get() != nullptr)
		pimpl_->setAppData(appData);
}

void lcss::KLVElement::Accept(Loki::BaseVisitor& visitor)
{
	if (pimpl_.get() == nullptr)
		return;
	pimpl_->Accept(visitor);
}

int lcss::KLVElement::compare(const lcss::KLVElement& element) const
{
	std::vector<uint8_t> lhs(16, 0x00);
	std::vector<uint8_t> rhs(16, 0x00);
	element.key(lhs.data());
	key(rhs.data());

	if (lhs == rhs)
		return 0;
	else if (lhs < rhs)
		return -1;

	return 1;
}
