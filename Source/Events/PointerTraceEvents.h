#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class GridEntity;
class MemoryGrid;

class PointerTraceEvents
{
public:
	static const std::string EventVictory;
	static const std::string EventEntityMoved;
	static const std::string EventRequestMovement;
	static const std::string EventResumeMovement;
	static const std::string EventWriteValue;
	static const std::string EventReadValue;
	static const std::string EventUpdateRegister;

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

	struct PointerTraceEntityMovedArgs
	{
		MemoryGrid* memoryGrid;
		GridEntity* gridEntity;
		PointerTraceRequestMovementArgs innerArgs;

		PointerTraceEntityMovedArgs(MemoryGrid* memoryGrid, GridEntity* gridEntity, PointerTraceRequestMovementArgs innerArgs) 
			: memoryGrid(memoryGrid), gridEntity(gridEntity), innerArgs(innerArgs) { } 
	};

	struct PointerTraceWriteArgs
	{
		int address;
		int value;

		PointerTraceWriteArgs(int address, int value) : address(address), value(value) { }
	};

	struct PointerTraceReadArgs
	{
		int address;
		std::function<void(int)> onReadCallback;

		PointerTraceReadArgs(int address, std::function<void(int)> onReadCallback) : address(address), onReadCallback(onReadCallback) { }
	};

	static void TriggerVictory();
	static void TriggerEntityMoved(PointerTraceEntityMovedArgs args);
	static void TriggerRequestMovement(PointerTraceRequestMovementArgs args);
	static void TriggerResumeMovement(PointerTraceRequestMovementArgs args);
	static void TriggerWriteValue(PointerTraceWriteArgs args);
	static void TriggerReadValue(PointerTraceReadArgs args);
	static void TriggerRegisterUpdated();
};
