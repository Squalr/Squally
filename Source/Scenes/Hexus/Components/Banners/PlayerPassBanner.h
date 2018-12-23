#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerPassBanner : public BannerBase
{
public:
	static PlayerPassBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	PlayerPassBanner();
	~PlayerPassBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerPassBanner1;
	cocos2d::Sprite* playerPassBanner2;
};
