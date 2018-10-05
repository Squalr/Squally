#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class OpponentFirstBanner : public BannerBase
{
public:
	static OpponentFirstBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	OpponentFirstBanner();
	~OpponentFirstBanner();

	void initializePositions() override;

	Sprite* enemyBanner1;
	Sprite* enemyBanner2;
};
