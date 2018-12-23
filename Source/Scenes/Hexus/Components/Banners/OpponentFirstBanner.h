#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class OpponentFirstBanner : public BannerBase
{
public:
	static OpponentFirstBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentFirstBanner();
	~OpponentFirstBanner();

	void initializePositions() override;

	cocos2d::Sprite* enemyBanner1;
	cocos2d::Sprite* enemyBanner2;
};
