#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

using namespace cocos2d;

class HandCardCountDisplay : public ComponentBase
{
public:
	static HandCardCountDisplay * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	HandCardCountDisplay();
	~HandCardCountDisplay();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	LayerColor* playerHandCardCountFrame;
	Label* playerHandCardCountText;
	Sprite* playerHandCardIcon;

	LayerColor* enemyHandCardCountFrame;
	Label* enemyHandCardCountText;
	Sprite* enemyHandCardIcon;
};
