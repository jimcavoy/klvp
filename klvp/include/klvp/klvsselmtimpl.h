#ifndef KLVSSELMTIMPL_H 
#define KLVSSELMTIMPL_H 
// klvsslex generated on Thu Aug 15 09:15:01 2013

#include <loki/Visitor.h>
#include "klvelmtimpl.h"

namespace lcss
{
	/***************************************************************************/
	// KLVSecurityElement
	class KLVSecurityElement
		:public KLVElementImpl
	{
	public:
		KLVSecurityElement();
		virtual ~KLVSecurityElement();
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	// KLVUnknownSecurity
	class KLVUnknownSecurity
		:public KLVElementImpl
	{
	public:
		KLVUnknownSecurity(uint8_t key);
		virtual ~KLVUnknownSecurity();
		LOKI_DEFINE_VISITABLE()
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVObjectCountryCodingMethodVersionDate
	class KLVObjectCountryCodingMethodVersionDate
		:public KLVSecurityElement
	{
	public:
		KLVObjectCountryCodingMethodVersionDate();
		virtual ~KLVObjectCountryCodingMethodVersionDate();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSecurityClassification
	class KLVSecurityClassification
		:public KLVSecurityElement
	{
	public:
		KLVSecurityClassification();
		virtual ~KLVSecurityClassification();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod
	class KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod
		:public KLVSecurityElement
	{
	public:
		KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod();
		virtual ~KLVClassifyingCountryandReleasingInstructionsCountryCodingMethod();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassifyingCountry
	class KLVClassifyingCountry
		:public KLVSecurityElement
	{
	public:
		KLVClassifyingCountry();
		virtual ~KLVClassifyingCountry();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVSecuritySCISHIinformation
	class KLVSecuritySCISHIinformation
		:public KLVSecurityElement
	{
	public:
		KLVSecuritySCISHIinformation();
		virtual ~KLVSecuritySCISHIinformation();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVCaveats
	class KLVCaveats
		:public KLVSecurityElement
	{
	public:
		KLVCaveats();
		virtual ~KLVCaveats();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVReleasingInstructions
	class KLVReleasingInstructions
		:public KLVSecurityElement
	{
	public:
		KLVReleasingInstructions();
		virtual ~KLVReleasingInstructions();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassifiedBy
	class KLVClassifiedBy
		:public KLVSecurityElement
	{
	public:
		KLVClassifiedBy();
		virtual ~KLVClassifiedBy();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVDerivedFrom
	class KLVDerivedFrom
		:public KLVSecurityElement
	{
	public:
		KLVDerivedFrom();
		virtual ~KLVDerivedFrom();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassificationReason
	class KLVClassificationReason
		:public KLVSecurityElement
	{
	public:
		KLVClassificationReason();
		virtual ~KLVClassificationReason();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVDeclassificationDate
	class KLVDeclassificationDate
		:public KLVSecurityElement
	{
	public:
		KLVDeclassificationDate();
		virtual ~KLVDeclassificationDate();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassificationandMarkingSystem
	class KLVClassificationandMarkingSystem
		:public KLVSecurityElement
	{
	public:
		KLVClassificationandMarkingSystem();
		virtual ~KLVClassificationandMarkingSystem();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVObjectCountryCodingMethod
	class KLVObjectCountryCodingMethod
		:public KLVSecurityElement
	{
	public:
		KLVObjectCountryCodingMethod();
		virtual ~KLVObjectCountryCodingMethod();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVObjectCountryCodes
	class KLVObjectCountryCodes
		:public KLVSecurityElement
	{
	public:
		KLVObjectCountryCodes();
		virtual ~KLVObjectCountryCodes();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassificationComments
	class KLVClassificationComments
		:public KLVSecurityElement
	{
	public:
		KLVClassificationComments();
		virtual ~KLVClassificationComments();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUMIDVideo
	class KLVUMIDVideo
		:public KLVSecurityElement
	{
	public:
		KLVUMIDVideo();
		virtual ~KLVUMIDVideo();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUMIDAudio
	class KLVUMIDAudio
		:public KLVSecurityElement
	{
	public:
		KLVUMIDAudio();
		virtual ~KLVUMIDAudio();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUMIDData
	class KLVUMIDData
		:public KLVSecurityElement
	{
	public:
		KLVUMIDData();
		virtual ~KLVUMIDData();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVUMIDSystem
	class KLVUMIDSystem
		:public KLVSecurityElement
	{
	public:
		KLVUMIDSystem();
		virtual ~KLVUMIDSystem();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVStreamID
	class KLVStreamID
		:public KLVSecurityElement
	{
	public:
		KLVStreamID();
		virtual ~KLVStreamID();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVTransportStreamID
	class KLVTransportStreamID
		:public KLVSecurityElement
	{
	public:
		KLVTransportStreamID();
		virtual ~KLVTransportStreamID();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVItemDesignator
	class KLVItemDesignator
		:public KLVSecurityElement
	{
	public:
		KLVItemDesignator();
		virtual ~KLVItemDesignator();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVVersion
	class KLVVersion
		:public KLVSecurityElement
	{
	public:
		KLVVersion();
		virtual ~KLVVersion();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
	/////////////////////////////////////////////////////////////////////////////
	//KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate
	class KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate
		:public KLVSecurityElement
	{
	public:
		KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate();
		virtual ~KLVClassifyingCountryandReleasingInstructionsCountryCodingMethodVersionDate();
		LIBKLVP_DEFINE_VISITABLE(lcss::KLVSecurityElement)
	};
}
#endif