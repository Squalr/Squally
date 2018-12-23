#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class DrawBanner : public BannerBase
{
public:
	static DrawBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DrawBanner();
	~DrawBanner();

	void initializePositions() override;

	cocos2d::Sprite* defeatBanner1;
	cocos2d::Sprite* defeatBanner2;
};
