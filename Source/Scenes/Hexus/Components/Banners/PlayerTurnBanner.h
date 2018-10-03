#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class PlayerTurnBanner : public BannerBase
{
public:
	static PlayerTurnBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	PlayerTurnBanner();
	~PlayerTurnBanner();

	void initializePositions() override;

	Sprite* playerBanner1;
	Sprite* playerBanner2;
};
