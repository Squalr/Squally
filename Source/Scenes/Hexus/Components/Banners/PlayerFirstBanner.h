#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerFirstBanner : public BannerBase
{
public:
	static PlayerFirstBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	PlayerFirstBanner();
	~PlayerFirstBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerBanner1;
	cocos2d::Sprite* playerBanner2;
};
