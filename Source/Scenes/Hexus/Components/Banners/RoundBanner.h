#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class RoundBanner : public BannerBase
{
public:
	static RoundBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	RoundBanner();
	~RoundBanner();

	void initializePositions() override;

	cocos2d::Sprite* roundBanner1;
	cocos2d::Sprite* roundBanner2;
};
