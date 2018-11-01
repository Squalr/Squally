#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class EnemyLastStandBanner : public BannerBase
{
public:
	static EnemyLastStandBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	EnemyLastStandBanner();
	~EnemyLastStandBanner();

	void initializePositions() override;

	Sprite* playerPassBanner1;
	Sprite* playerPassBanner2;
};
