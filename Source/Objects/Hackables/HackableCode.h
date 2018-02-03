#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"

using namespace cocos2d;

class HackableCode : public HackableAttribute
{
public:
	static HackableCode * create(std::string name, void* codeStart, int codeLength);

	void* allocateMemory(int allocationSize);

	std::string functionName;
	void* codePointer;
	int codeOriginalLength;
	std::map<void*, int>* allocations;

private:
	HackableCode(std::string name, void* codeStart, int codeLength);
	~HackableCode();
};

