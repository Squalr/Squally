#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

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

	void initializePositions() override;
	void doCoinFlip(GameState* gameState);

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;
};
