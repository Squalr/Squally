#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerLastStandBanner : public BannerBase
{
public:
	static PlayerLastStandBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	PlayerLastStandBanner();
	~PlayerLastStandBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerPassBanner1;
	cocos2d::Sprite* playerPassBanner2;
};
