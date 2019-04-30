#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class PointerTraceEvents
{
public:
	static const std::string EventInitializeRegisters;

	struct PointerTraceInitializeRegistersArgs
	{
		int eax;
		int ebx;
		int ecx;
		int edx;
		int edi;
		int esi;
		int ebp;
		int esp;
		int eip;

		PointerTraceInitializeRegistersArgs() : eax(0), ebx(0), ecx(0), edx(0), edi(0), esi(0), ebp(0), esp(0), eip(0)
		{
		}
	};

	static void TriggerInitializeRegisters(PointerTraceInitializeRegistersArgs args);
};
