#pragma once

#include "Events/PointerTraceEvents.h"
#include "Scenes/MapBase.h"

class GridEntity;
class MemoryGrid;

class PointerTraceMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	PointerTraceMap();
	~PointerTraceMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void buildCollisionMaps();
	void initializeGridObjects();
	void moveGridEntity(PointerTraceEvents::PointerTraceRequestMovementArgs* args);

	std::map<int, bool> collisionMap;
	std::map<int, bool> segfaultMap;
	MemoryGrid* memoryGrid;

	static PointerTraceMap* instance;
};
