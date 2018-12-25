#pragma once
#include <map>
#include <string>

#include "Engine/Hackables/HackableAttribute.h"

#ifndef _WIN32
	#include <sys/mman.h>
#endif

// These allow for MACRO overloading
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define ASM(...) GET_MACRO(__VA_ARGS__, ASM3, ASM2, ASM1)(__VA_ARGS__)

// These allow for the creation of unique labels for hackable code
#define TOKEN_PASTE(x, y) x ## y
#define TOKEN_PASTE2(x, y) TOKEN_PASTE(x, y)
#define LABEL_CREATE TOKEN_PASTE2(label, __LINE__)

// Define macros for inlining x86 assembly in a compiler-independent way
#ifdef _MSC_VER
	#define ASM1(asm_literal) \
        	__asm asm_literal
	#define ASM2(asm_literal1, asm_literal2) \
        	__asm asm_literal1, asm_literal2
	#define ASM3(asm_literal1, asm_literal2, asm_literal3) \
        	__asm asm_literal1, asm_literal2, asm_literal3
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

#define HACKABLE_CODE_BEGIN(address) \
ASM(mov address, offset LABEL_CREATE) \
ASM(LABEL_CREATE):


#define HACKABLE_CODE_END(address) \
ASM(LABEL_CREATE): \
ASM(mov address, offset LABEL_CREATE)

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
	std::map<void*, int> allocations;

private:
	HackableCode(std::string name, void* codeStart, int codeLength, std::string iconResource);
	virtual ~HackableCode();
};
