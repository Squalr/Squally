#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableAttribute.h"

#ifndef _WIN32
	#include <sys/mman.h>
#endif

#ifdef _MSC_VER
#   define ASM(asm_literal) \
        __asm { \
            asm_literal \
        };
#elif __GNUC__ || __clang__
#   define ASM(asm_literal) \
        "__asm__(\".intel_syntax noprefix\");" \
        "__asm__(\"" \
            #asm_literal \
        "\" : : );" \
        "__asm__(\".att_syntax prefix\");"
#endif

#define HACKABLE_CODE_BEGIN(address, label) \
ASM("mov address, offset label") \
ASM(label:)

#define HACKABLE_CODE_END(address, label) \
ASM(label:) \
ASM("mov address, offset label")

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

