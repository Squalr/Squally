#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentFirstBanner : public BannerBase
{
public:
	static OpponentFirstBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentFirstBanner();
	~OpponentFirstBanner();

	void initializePositions() override;

	cocos2d::Sprite* enemyBanner1;
	cocos2d::Sprite* enemyBanner2;
};
