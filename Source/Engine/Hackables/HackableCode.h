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

	// Windows likes to optimize out bytes that are directly emitted, so all hackable function tags are a sequence of useless instructions instead

	// 56 6A * BE DE C0 ED FE 5E 5E
	#define HACKABLE_CODE_BEGIN(func_id) \
		ASM(push EDI) \
		ASM(push func_id) \
		ASM(mov EDI, 0xFEEDC0DE) \
		ASM(pop EDI) \
		ASM(pop EDI)

	// 56 6A 45 BE DE C0 AD DE 5E 5E
	#define HACKABLE_CODE_END() \
		ASM(push ESI) \
		ASM(push 69) \
		ASM(mov ESI, 0xDEADC0DE) \
		ASM(pop ESI) \
		ASM(pop ESI)

	// 56 6A 45 BE 5E EA 5E D1 5E 5E
	#define HACKABLES_STOP_SEARCH() \
		ASM(push EDX) \
		ASM(push 69) \
		ASM(mov EDX, 0x0D15EA5E) \
		ASM(pop EDX) \
		ASM(pop EDX)
#elif __GNUC__ || __clang__
	#define ASM1(asm_literal) \
		ASM_GCC(#asm_literal)
	#define ASM2(asm_literal1, asm_literal2) \
		ASM_GCC(#asm_literal1 ", " #asm_literal2)
	#define ASM3(asm_literal1, asm_literal2, asm_literal3) \
		ASM_GCC(#asm_literal1 ", " #asm_literal2 ", " #asm_literal3)

	#define ASM_GCC(asm_string) \
		__asm__(".intel_syntax noprefix;" asm_string ";.att_syntax prefix"); \

	#define HACKABLE_CODE_BEGIN(func_id) \
		__asm__(".byte 0x57, 0x6A, " func_id ", 0xBF, 0xDE, 0xC0, 0xED, 0xFE, 0x5F, 0x5F")
	#define HACKABLE_CODE_END() \
		__asm__(".byte 0x56, 0x6A, 0x45, 0xBE, 0xDE, 0xC0, 0xAD, 0xDE, 0x5E, 0x5E")
	#define HACKABLES_STOP_SEARCH() \
		__asm__(".byte 0x52, 0x6A, 0x45, 0xBA, 0x5E, 0xEA, 0x15, 0x0D, 0x5A, 0x5A")
#endif

#define ASM_NOP1() ASM(nop)
#define ASM_NOP2() ASM_NOP1() ASM_NOP1()
#define ASM_NOP3() ASM_NOP2() ASM_NOP1()
#define ASM_NOP4() ASM_NOP3() ASM_NOP1()
#define ASM_NOP5() ASM_NOP4() ASM_NOP1()
#define ASM_NOP6() ASM_NOP5() ASM_NOP1()
#define ASM_NOP7() ASM_NOP6() ASM_NOP1()
#define ASM_NOP8() ASM_NOP7() ASM_NOP1()

class LocalizedString;

class HackableCode : public HackableAttribute
{
public:
	struct LateBindData
	{
		LocalizedString* functionName;
		std::string iconResource;

		LateBindData() : functionName(nullptr), iconResource("") { }
		LateBindData(LocalizedString* functionName, std::string iconResource) : functionName(functionName), iconResource(iconResource) { }
	};

	static std::vector<HackableCode*> create(void* functionStart, std::map<unsigned char, LateBindData>& lateBindDataMap);

	std::string getAssemblyString();
	LocalizedString* getFunctionName();
	void* getCodePointer();
	int getOriginalLength();
	bool applyCustomCode(std::string newAssembly);
	void restoreOriginalCode();
	void* allocateMemory(int allocationSize);

	static std::map<void*, std::vector<HackableCode*>> HackableCodeCache;
	static const int StartTagFuncIdIndex;
	static const unsigned char StartTagSignature[];
	static const unsigned char EndTagSignature[];
	static const unsigned char StopSearchTagSignature[];

private:
	static HackableCode* create(void* codeStart, void* codeEnd, LocalizedString* functionName, std::string iconResource);

	HackableCode(void* codeStart, void* codeEnd, LocalizedString* functionName, std::string iconResource);
	virtual ~HackableCode();

	std::string assemblyString;
	LocalizedString* functionName;
	void* codePointer;
	unsigned char* originalCodeCopy;
	int originalCodeLength;
	std::map<void*, int> allocations;
};
