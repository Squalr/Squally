#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class OpponentRoundWinBanner : public BannerBase
{
public:
	static OpponentRoundWinBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentRoundWinBanner();
	~OpponentRoundWinBanner();

	void initializePositions() override;

	Sprite* playerPassBanner1;
	Sprite* playerPassBanner2;
};
