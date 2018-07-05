#pragma once
#include "cocos2d.h"

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

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void updateBanner(GameState* gameState);

	LayerColor* statusBanner;
	Label* statusLabel;
};
