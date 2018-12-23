#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class VictoryBanner : public BannerBase
{
public:
	static VictoryBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	VictoryBanner();
	~VictoryBanner();

	void initializePositions() override;

	cocos2d::Sprite* victoryBanner1;
	cocos2d::Sprite* victoryBanner2;
};
