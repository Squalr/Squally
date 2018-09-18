#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableAttribute.h"

#ifndef _WIN32
	#include <sys/mman.h>
#endif

#define HACKABLE_CODE_BEGIN(address, label) \
_asm \
{ \
	_asm mov address, offset label \
	_asm label: \
}

#define HACKABLE_CODE_END(address, label) \
_asm \
{ \
	_asm label: \
	_asm mov address, offset label \
}

using namespace cocos2d;

class HackableCode : public HackableAttribute
{
public:
	static HackableCode * create(std::string name, void* codeStart, int codeLength, std::string iconResource);

	void restoreOriginalCode();
	bool applyCustomCode();
	void* allocateMemory(int allocationSize);

	std::string assemblyString;
	std::string functionName;
	void* codePointer;
	void* originalCodeCopy;
	int codeOriginalLength;
	std::map<void*, int>* allocations;

private:
	HackableCode(std::string name, void* codeStart, int codeLength, std::string iconResource);
	~HackableCode();
};

