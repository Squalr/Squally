#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Resources.h"

using namespace cocos2d;

class Fight : public FadeScene
{
public:
	static Fight* create();

	void loadFight(Squally* squally, PlatformerEnemy* enemy);

protected:
	Fight();
	~Fight();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	Layer * background;
	Layer * entityLayer;
	Layer * objectLayer;
};
