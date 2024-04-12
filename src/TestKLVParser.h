#pragma once
#include <klvp/klvprsr.h>

#include "KLVPrintVisitor.h"

namespace klv2xml
{
	/// @brief 
	class TestKLVParser :
		public lcss::KLVParser
	{
	public:
		TestKLVParser(KLVPrintVisitor& printer);
		virtual ~TestKLVParser(void);

		void onBeginSet(int len, lcss::TYPE type) override;
		void onElement(lcss::KLVElement& klv) override;
		void onEndSet() override;
		void onError(const char* errmsg, int pos) override;

		int count() const { return count_; }

	private:
		int					count_;
		lcss::TYPE			type_;
		KLVPrintVisitor&	printVisitor_;
	};


}