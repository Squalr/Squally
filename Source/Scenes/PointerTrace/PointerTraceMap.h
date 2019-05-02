#pragma once
#include <set>

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
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void onEnter() override;
	void buildCollisionMaps();
	void initializeGridObjects();
	void moveGridEntity(PointerTraceEvents::PointerTraceRequestMovementArgs args);

	std::set<int> collisionMap;
	std::set<int> segfaultMap;
	MemoryGrid* memoryGrid;
	cocos2d::Node* collisionDebugNode;

	static PointerTraceMap* instance;
};
