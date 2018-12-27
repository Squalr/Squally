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

#if (_WIN64 || (__GNUC__ && (__x86_64__ || __ppc64__)))
	#define EAX rax
	#define EBX rbx
	#define ECX rcx
	#define EDX rdx
	#define ESI rsi
	#define EDI rdi
	#define EBP rbp
	#define ESP rsp
#else
	#define EAX eax
	#define EBX ebx
	#define ECX ecx
	#define EDX edx
	#define ESI esi
	#define EDI edi
	#define EBP ebp
	#define ESP esp
#endif

// Define macros for inlining x86 assembly in a compiler-independent way
#ifdef _MSC_VER
	#define ASM1(asm_literal) \
		__asm asm_literal
	#define ASM2(asm_literal1, asm_literal2) \
		__asm asm_literal1, asm_literal2
	#define ASM3(asm_literal1, asm_literal2, asm_literal3) \
		__asm asm_literal1, asm_literal2, asm_literal3
	#define HACKABLE_CODE_BEGIN(address) \
		__asm _emit 0x66, __asm _emit 0x66, __asm _emit 0x66, __asm _emit 0x0F, __asm _emit 0x1F, __asm _emit 0x84, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00
	#define HACKABLE_CODE_END(address) \
		__asm _emit 0x66, __asm _emit 0x66, __asm _emit 0x66, __asm _emit 0x0F, __asm _emit 0x1F, __asm _emit 0x84, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00, __asm _emit 0x00
#elif __GNUC__ || __clang__
	#define ASM1(asm_literal) \
		ASM_GCC(#asm_literal)
	#define ASM2(asm_literal1, asm_literal2) \
		ASM_GCC(#asm_literal1 ", " #asm_literal2)
	#define ASM3(asm_literal1, asm_literal2, asm_literal3) \
		ASM_GCC(#asm_literal1 ", " #asm_literal2 ", " #asm_literal3)

	#define ASM_GCC(asm_string) \
		__asm__(".intel_syntax noprefix;" asm_string ";.att_syntax prefix"); \

	#define HACKABLE_CODE_BEGIN(address) \
		__asm__(".byte 0x66, 0x66, 0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00")
	#define HACKABLE_CODE_END(address) \
		__asm__(".byte 0x66, 0x66, 0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00")
#endif

#define ASM_NOP1() ASM(nop)
#define ASM_NOP2() ASM_NOP1() ASM_NOP1()
#define ASM_NOP3() ASM_NOP2() ASM_NOP1()
#define ASM_NOP4() ASM_NOP3() ASM_NOP1()
#define ASM_NOP5() ASM_NOP4() ASM_NOP1()
#define ASM_NOP6() ASM_NOP5() ASM_NOP1()
#define ASM_NOP7() ASM_NOP6() ASM_NOP1()
#define ASM_NOP8() ASM_NOP7() ASM_NOP1()

class HackableCode : public HackableAttribute
{
public:
	static HackableCode* create(std::string name, void* codeStart, int codeLength, std::string iconResource);

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
