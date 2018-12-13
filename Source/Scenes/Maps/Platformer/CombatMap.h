#pragma once
#include "cocos2d.h"

#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Maps/MapBase.h"

using namespace cocos2d;

class CombatMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	CombatMap();
	~CombatMap();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	static CombatMap* instance;
};
