#pragma once
#include "cocos2d.h"

#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"

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
	void initializePositions() override;
	void initializeListeners() override;

	Layer * background;
	Layer * entityLayer;
	Layer * objectLayer;
};
