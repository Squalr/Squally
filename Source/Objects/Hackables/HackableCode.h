#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"

using namespace cocos2d;

class HackableCode : public HackableAttribute
{
public:
	static HackableCode * create(void* codeStart, int codeLength);

private:
	HackableCode(void* codeStart, int codeLength);
	~HackableCode();

	void* codePointer;
	int codeOriginalLength;
};

