#ifndef KLVSecuritySetPrintVisitor_H
#define KLVSecuritySetPrintVisitor_H

// klvsslex generated on Tue Aug 06 10:36:49 2013
#include <klvp/klvelmt.h>
#include <klvp/klvsselmtimpl.h>

#include <loki/Visitor.h>

class KLVSecuritySetPrintVisitor
	: public Loki::BaseVisitor,
	public Loki::Visitor<lcss::KLVUnknownSecurity>,
	public Loki::Visitor<lcss::KLVParseError>,
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
	KLVSecuritySetPrintVisitor();

	void Visit(lcss::KLVUnknownSecurity& klv);
	void Visit(lcss::KLVParseError& klv);
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
};
#endif