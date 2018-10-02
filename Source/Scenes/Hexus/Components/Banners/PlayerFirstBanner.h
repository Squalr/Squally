#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class PlayerFirstBanner : public BannerBase
{
public:
	static PlayerFirstBanner * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	PlayerFirstBanner();
	~PlayerFirstBanner();

	void initializePositions() override;
};
