#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class HackableCode : public Node
{
public:
	static HackableCode * create(byte* codeStart, int codeLength);

private:
	HackableCode(byte* codeStart, int codeLength);
	~HackableCode();

	byte* codePointer;
	int codeOriginalLength;
};

