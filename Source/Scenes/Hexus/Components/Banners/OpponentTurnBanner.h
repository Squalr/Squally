#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class OpponentTurnBanner : public BannerBase
{
public:
	static OpponentTurnBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentTurnBanner();
	~OpponentTurnBanner();

	void initializePositions() override;

	Sprite* enemyBanner1;
	Sprite* enemyBanner2;
};
