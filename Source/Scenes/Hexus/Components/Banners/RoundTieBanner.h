#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class RoundTieBanner : public BannerBase
{
public:
	static RoundTieBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	RoundTieBanner();
	~RoundTieBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerPassBanner1;
	cocos2d::Sprite* playerPassBanner2;
};
