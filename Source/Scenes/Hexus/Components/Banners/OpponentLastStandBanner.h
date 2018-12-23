#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentLastStandBanner : public BannerBase
{
public:
	static OpponentLastStandBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentLastStandBanner();
	~OpponentLastStandBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerPassBanner1;
	cocos2d::Sprite* playerPassBanner2;
};
