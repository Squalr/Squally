#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerTurnBanner : public BannerBase
{
public:
	static PlayerTurnBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	PlayerTurnBanner();
	~PlayerTurnBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerBanner1;
	cocos2d::Sprite* playerBanner2;
};
