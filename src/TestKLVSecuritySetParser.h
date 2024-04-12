#pragma once
#include <klvp/klvprsr.h>

#include "KLVSecuritySetPrintVisitor.h"

namespace klv2xml
{
	class TestKLVSecuritySetParser :
		public lcss::KLVSecuritySetParser
	{
	public:
		TestKLVSecuritySetParser(void);
		virtual ~TestKLVSecuritySetParser(void);

		virtual void onBeginSet(int len, lcss::TYPE type);
		virtual void onElement(lcss::KLVElement& klv);
		virtual void onEndSet();
		virtual void onError(const char* errmsg, int pos);

	private:
		KLVSecuritySetPrintVisitor	printVisitor_;
	};
}
