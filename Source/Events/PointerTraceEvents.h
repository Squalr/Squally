#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class GridEntity;
class MemoryGrid;

class PointerTraceEvents
{
public:
	static const std::string EventEntityMoved;
	static const std::string EventRequestMovement;
	static const std::string EventResumeMovement;
	static const std::string EventInitializeRegisters;

	struct PointerTraceRequestMovementArgs
	{
		enum Direction
		{
			Up,
			Down,
			Left,
			Right
		};

		GridEntity* gridEntity;
		Direction direction;
		int source;
		float speed;

		PointerTraceRequestMovementArgs(GridEntity* gridEntity, Direction direction, int source, float speed)
			: gridEntity(gridEntity), direction(direction), source(source), speed(speed) { } 
	};

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

	struct PointerTraceEntityMovedArgs
	{
		MemoryGrid* memoryGrid;
		GridEntity* gridEntity;
		PointerTraceRequestMovementArgs innerArgs;

		PointerTraceEntityMovedArgs(MemoryGrid* memoryGrid, GridEntity* gridEntity, PointerTraceRequestMovementArgs innerArgs) 
			: memoryGrid(memoryGrid), gridEntity(gridEntity), innerArgs(innerArgs) { } 
	};

	static void TriggerEntityMoved(PointerTraceEntityMovedArgs args);
	static void TriggerRequestMovement(PointerTraceRequestMovementArgs args);
	static void TriggerResumeMovement(PointerTraceRequestMovementArgs args);
	static void TriggerInitializeRegisters(PointerTraceInitializeRegistersArgs args);
};
