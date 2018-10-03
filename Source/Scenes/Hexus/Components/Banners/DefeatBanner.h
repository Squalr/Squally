#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class DefeatBanner : public BannerBase
{
public:
	static DefeatBanner * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	DefeatBanner();
	~DefeatBanner();

	void initializePositions() override;
};
