#include "HackableCode.h"

HackableCode * HackableCode::create(void* codeStart, int codeLength)
{
	HackableCode* hackableCode = new HackableCode(codeStart, codeLength);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(void* codeStart, int codeLength)
{
	this->codePointer = codeStart;
	this->codeOriginalLength = codeLength;
}

HackableCode::~HackableCode()
{
}
