#include "HackableCode.h"

HackableCode * HackableCode::create(std::string name, void* codeStart, int codeLength)
{
	HackableCode* hackableCode = new HackableCode(name, codeStart, codeLength);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(std::string name, void* codeStart, int codeLength)
{
	this->functionName = name;
	this->codePointer = (byte*)codeStart;
	this->codeOriginalLength = codeLength;
}

HackableCode::~HackableCode()
{
}
