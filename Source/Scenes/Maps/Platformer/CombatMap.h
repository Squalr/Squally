#pragma once
#include "cocos2d.h"

#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Maps/IMap.h"

using namespace cocos2d;

class CombatMap : public IMap
{
public:
	static void registerGlobalScene();

	void loadMap(SerializableMap* serializableMap) override;

protected:
	CombatMap();
	~CombatMap();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Node* mapNode;
	SerializableMap* map;

	static CombatMap* instance;
};
