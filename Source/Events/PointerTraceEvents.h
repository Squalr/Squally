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
	static const std::string EventResetState;

	struct PointerTraceRequestMovementArgs
	{
		enum Direction
		{
			Up,
			Down,
			Left,
			Right
		};

		GridEntity* gridEntity = nullptr;
		Direction direction = Direction::Up;
		int source = 0;
		float speed = 0.0f;

		PointerTraceRequestMovementArgs(GridEntity* gridEntity, Direction direction, int source, float speed)
			: gridEntity(gridEntity), direction(direction), source(source), speed(speed) { } 
	};

	struct PointerTraceEntityMovedArgs
	{
		MemoryGrid* memoryGrid = nullptr;
		GridEntity* gridEntity = nullptr;
		PointerTraceRequestMovementArgs innerArgs;

		PointerTraceEntityMovedArgs(MemoryGrid* memoryGrid, GridEntity* gridEntity, PointerTraceRequestMovementArgs innerArgs) 
			: memoryGrid(memoryGrid), gridEntity(gridEntity), innerArgs(innerArgs) { } 
	};

	struct PointerTraceWriteArgs
	{
		int address = 0;
		int value = 0;

		PointerTraceWriteArgs(int address, int value) : address(address), value(value) { }
	};

	struct PointerTraceReadArgs
	{
		int address = 0;
		std::function<void(int)> onReadCallback = nullptr;

		PointerTraceReadArgs(int address, std::function<void(int)> onReadCallback) : address(address), onReadCallback(onReadCallback) { }
	};

	static void TriggerVictory();
	static void TriggerEntityMoved(PointerTraceEntityMovedArgs args);
	static void TriggerRequestMovement(PointerTraceRequestMovementArgs args);
	static void TriggerResumeMovement(PointerTraceRequestMovementArgs args);
	static void TriggerWriteValue(PointerTraceWriteArgs args);
	static void TriggerReadValue(PointerTraceReadArgs args);
	static void TriggerRegisterUpdated();
	static void TriggerResetState();
};
