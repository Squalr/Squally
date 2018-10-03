#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class RoundBanner : public BannerBase
{
public:
	static RoundBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	RoundBanner();
	~RoundBanner();

	void initializePositions() override;

	Sprite* roundBanner1;
	Sprite* roundBanner2;
};
