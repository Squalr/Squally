#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class StateCoinFlip : public ComponentBase
{
public:
	static StateCoinFlip * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	StateCoinFlip();
	~StateCoinFlip();

	void initializePositions() override;
	void doCoinFlip(GameState* gameState);

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;
};
