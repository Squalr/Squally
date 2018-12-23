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
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentTurnBanner();
	~OpponentTurnBanner();

	void initializePositions() override;

	cocos2d::Sprite* enemyBanner1;
	cocos2d::Sprite* enemyBanner2;
};
