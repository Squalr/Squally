#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"

using namespace cocos2d;

class HackableCode : public HackableAttribute
{
public:
	static HackableCode * create(std::string name, void* codeStart, int codeLength);

	std::string functionName;
	void* codePointer;
	int codeOriginalLength;

private:
	HackableCode(std::string name, void* codeStart, int codeLength);
	~HackableCode();
};

