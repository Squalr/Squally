#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class PlayerFirstBanner : public BannerBase
{
public:
	static PlayerFirstBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	PlayerFirstBanner();
	~PlayerFirstBanner();

	void initializePositions() override;

	Sprite* playerBanner1;
	Sprite* playerBanner2;
};
