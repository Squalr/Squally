#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class CardReplaceBanner : public BannerBase
{
public:
	static CardReplaceBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	CardReplaceBanner();
	~CardReplaceBanner();

	void initializePositions() override;
};
