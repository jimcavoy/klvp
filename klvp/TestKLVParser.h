#pragma once
#include "klvprsr.h"
#include "KLVPrintVisitor.h"

class TestKLVParser :
	public lcss::KLVParser
{
public:
	TestKLVParser(KLVPrintVisitor& printer);
	virtual ~TestKLVParser(void);

	virtual void onBeginSet(int len, lcss::TYPE type);
	virtual void onElement( lcss::KLVElement& klv);
	virtual void onEndSet();
	virtual void onError(const char* errmsg, int pos);

	int count() const { return count_; }

private:
	int						count_;
	lcss::TYPE	type_;
	KLVPrintVisitor&		printVisitor_;
};

