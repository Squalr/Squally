#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableAttribute.h"

#ifndef _WIN32
	#include <sys/mman.h>
#endif

// These allow for MACRO overloading
#define CAT( A, B ) A ## B
#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define GET_COUNT( _1, _2, _3, _4, _5, _6, COUNT, ... ) COUNT
#define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, 6, 5, 4, 3, 2, 1 )
#define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

// Define macros for inlining x86 assembly in a compiler-independent way
#ifdef _MSC_VER
	#define ASM( ... ) VA_SELECT( ASM, __VA_ARGS__ )
	#define ASM_1(asm_literal) \
        	"__asm " #asm_literal ";"
	#define ASM_2(asm_literal1, asm_literal2) \
        	"__asm " #asm_literal1 ", " #asm_literal2 ";"
	#define ASM_3(asm_literal1, asm_literal2, asm_literal3) \
        	"__asm " #asm_literal1 ", " #asm_literal2 ", " #asm_literal3 ";"
#elif __GNUC__ || __clang__
	#define ASM( ... ) VA_SELECT( ASM, __VA_ARGS__ )
	#define ASM_1(asm_literal) \
		"__asm__(\".intel_syntax noprefix\");" \
		"__asm__(\"" \
		#asm_literal \
		"\" : : );" \
		"__asm__(\".att_syntax prefix\");"
	#define ASM_2(asm_literal1, asm_literal2) \
		"__asm__(\".intel_syntax noprefix\");" \
		"__asm__(\"" \
		#asm_literal1 ", " #asm_literal2 \
		"\" : : );" \
		"__asm__(\".att_syntax prefix\");"
	#define ASM_3(asm_literal1, asm_literal2, asm_literal3) \
		"__asm__(\".intel_syntax noprefix\");" \
		"__asm__(\"" \
		#asm_literal1 ", " #asm_literal2 ", " #asm_literal3 \
		"\" : : );" \
		"__asm__(\".att_syntax prefix\");"
#endif

#define HACKABLE_CODE_BEGIN(address, label) \
ASM_2("mov " #address, "offset " #label) \
ASM_1(label:)

#define HACKABLE_CODE_END(address, label) \
ASM_1(label:) \
ASM_2("mov " #address, "offset " #label)

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

