#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class CoinFlip : public ComponentBase
{
public:
	static CoinFlip * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	CoinFlip();
	~CoinFlip();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void doCoinFlip(GameState* gameState);

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;
};
