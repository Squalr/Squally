#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

using namespace cocos2d;

class Banners : public ComponentBase
{
public:
	static Banners * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	Banners();
	~Banners();

	void initializePositions() override;
	void updateBanner(GameState* gameState);

	LayerColor* statusBanner;
	Label* statusLabel;
};
