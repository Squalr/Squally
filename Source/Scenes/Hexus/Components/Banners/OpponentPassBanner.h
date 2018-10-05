#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class OpponentPassBanner : public BannerBase
{
public:
	static OpponentPassBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	OpponentPassBanner();
	~OpponentPassBanner();

	void initializePositions() override;

	Sprite* opponentPassBanner1;
	Sprite* opponentPassBanner2;
};
