#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/GameState.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class CoinFlip : public Node
{
public:
	static CoinFlip * create();

	static const std::string HexiumGameStartEvent;
	static const std::string HexiumGameEndEvent;


private:
	CoinFlip();
	~CoinFlip();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void doCoinFlip(GameState* gameState);
	void onStateChange(EventCustom* eventCustom);

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;
};
