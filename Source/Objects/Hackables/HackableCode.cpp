#include "HackableCode.h"

HackableCode * HackableCode::create(byte* codeStart, int codeLength)
{
	HackableCode* hackableCode = new HackableCode(codeStart, codeLength);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(byte* codeStart, int codeLength)
{
	this->codePointer = codeStart;
	this->codeOriginalLength = codeLength;
}

HackableCode::~HackableCode()
{
}
