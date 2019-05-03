#pragma once
#include <set>

#include "Events/PointerTraceEvents.h"
#include "Scenes/MapBase.h"

class GridEntity;
class MemoryGrid;
class SegfaultMenu;
class VictoryMenu;

class PointerTraceMap : public MapBase
{
public:
	static void registerGlobalScene();

	void loadMap(std::string mapResource) override;

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
	void update(float dt) override;
	void buildCollisionMaps();
	void initializeGridObjects();
	void tryResumeMovement(PointerTraceEvents::PointerTraceRequestMovementArgs args);
	void moveGridEntity(PointerTraceEvents::PointerTraceRequestMovementArgs args);
	void openSegfaultMenu();
	void openVictoryMenu();

	std::set<int> collisionMap;
	std::set<int> segfaultMap;
	MemoryGrid* memoryGrid;
	cocos2d::Node* collisionDebugNode;
	SegfaultMenu* segfaultMenu;
	VictoryMenu* victoryMenu;

	static PointerTraceMap* instance;
};
