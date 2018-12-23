#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class DefeatBanner : public BannerBase
{
public:
	static DefeatBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DefeatBanner();
	~DefeatBanner();

	void initializePositions() override;

	cocos2d::Sprite* defeatBanner1;
	cocos2d::Sprite* defeatBanner2;
};
