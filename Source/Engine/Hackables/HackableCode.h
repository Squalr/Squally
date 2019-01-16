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

#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)

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

	#define ASM_MOV_REG_VAR(register, variable) \
		ASM(mov register, variable)

	#define ASM_MOV_VAR_REG(variable, register) \
		ASM(mov variable, register)

	// Directly emitting bytes wasn't working, so we just produce the assembly required for the signatures

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

	// Clang chokes on intel syntax when dealing with binding C variables -- just use AT&T syntax for these
	#define ASM_MOV_REG_VAR(register, variable) \
		__asm__ __volatile__("mov %0, %%" EXPAND_AND_QUOTE(register)  : : "m"(variable) : )

	#define ASM_MOV_VAR_REG(variable, register) \
		__asm__ __volatile__("mov %%" EXPAND_AND_QUOTE(register) ", %0"  : "=m"(variable) : : )

	#define ASM_GCC(asm_string) \
		__asm__ __volatile__(".intel_syntax noprefix;" asm_string ";.att_syntax prefix"); \

	#define HACKABLE_CODE_BEGIN(func_id) \
		__asm__ __volatile__(".byte 0x57, 0x6A, " EXPAND_AND_QUOTE(func_id) ", 0xBF, 0xDE, 0xC0, 0xED, 0xFE, 0x5F, 0x5F")
	#define HACKABLE_CODE_END() \
		__asm__ __volatile__(".byte 0x56, 0x6A, 0x45, 0xBE, 0xDE, 0xC0, 0xAD, 0xDE, 0x5E, 0x5E")
	#define HACKABLES_STOP_SEARCH() \
		__asm__ __volatile__(".byte 0x52, 0x6A, 0x45, 0xBA, 0x5E, 0xEA, 0x15, 0x0D, 0x5A, 0x5A")
#endif

#define ASM_NOP1() ASM(nop)
#define ASM_NOP2() ASM_NOP1() ASM_NOP1()
#define ASM_NOP3() ASM_NOP2() ASM_NOP1()
#define ASM_NOP4() ASM_NOP3() ASM_NOP1()
#define ASM_NOP5() ASM_NOP4() ASM_NOP1()
#define ASM_NOP6() ASM_NOP5() ASM_NOP1()
#define ASM_NOP7() ASM_NOP6() ASM_NOP1()
#define ASM_NOP8() ASM_NOP7() ASM_NOP1()

class HackablePreview;
class LocalizedString;

class HackableCode : public HackableAttribute
{
public:
	enum Register
	{
		eax,
		ebx,
		ecx,
		edx,
		edi,
		esi,
		ebp,
		esp,
		eip,
		rax,
		rbx,
		rcx,
		rdx,
		rdi,
		rsi,
		rbp,
		rsp,
		rip,
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		r14,
		r15,
	};

	struct LateBindData
	{
		std::string hackableObjectIdentifier;
		LocalizedString* functionName;
		std::string iconResource;
		HackablePreview* hackablePreview;
		std::map<Register, LocalizedString*> registerHints;

		LateBindData() : hackableObjectIdentifier(""), functionName(nullptr), iconResource(""), hackablePreview(nullptr), registerHints({ }) { }
		LateBindData(std::string hackableIdentifier, LocalizedString* functionName, std::string iconResource, HackablePreview* hackablePreview, std::map<Register, LocalizedString*> registerHints) :
			hackableObjectIdentifier(hackableIdentifier), functionName(functionName), iconResource(iconResource), hackablePreview(hackablePreview), registerHints(registerHints) { }
	};

	static std::vector<HackableCode*> create(void* functionStart, std::map<unsigned char, LateBindData>& lateBindDataMap);

	std::string getHackableCodeIdentifier();
	std::string getAssemblyString();
	std::string getOriginalAssemblyString();
	void* getCodePointer();
	int getOriginalLength();
	bool applyCustomCode(std::string newAssembly);
	void restoreOriginalCode();
	void* allocateMemory(int allocationSize);

	std::map<Register, LocalizedString*> registerHints;

	static std::map<void*, std::vector<HackableCode*>> HackableCodeCache;
	static const int StartTagFuncIdIndex;
	static const unsigned char StartTagSignature[];
	static const unsigned char EndTagSignature[];
	static const unsigned char StopSearchTagSignature[];

private:
	typedef HackableAttribute super;
	static HackableCode* create(void* codeStart, void* codeEnd, LateBindData lateBindData);

	HackableCode(void* codeStart, void* codeEnd, LateBindData lateBindData);
	virtual ~HackableCode();

	std::string hackableCodeIdentifier;
	std::string assemblyString;
	std::string originalAssemblyString;
	void* codePointer;
	unsigned char* originalCodeCopy;
	int originalCodeLength;
	std::map<void*, int> allocations;
};
