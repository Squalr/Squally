#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateCoinFlip : public StateBase
{
public:
	static StateCoinFlip * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateCoinFlip();
	~StateCoinFlip();

	void onEnter() override;
	void initializePositions() override;

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;
};
