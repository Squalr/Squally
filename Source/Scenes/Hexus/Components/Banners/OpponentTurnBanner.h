#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentTurnBanner : public BannerBase
{
public:
	static OpponentTurnBanner* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;
	OpponentTurnBanner();
	~OpponentTurnBanner();

	void initializePositions() override;

	cocos2d::Sprite* enemyBanner1;
	cocos2d::Sprite* enemyBanner2;
};
