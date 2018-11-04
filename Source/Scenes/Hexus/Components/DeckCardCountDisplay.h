#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class DeckCardCountDisplay : public ComponentBase
{
public:
	static DeckCardCountDisplay * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DeckCardCountDisplay();
	~DeckCardCountDisplay();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	LayerColor* playerDeckCardCountFrame;
	Label* playerDeckCardCountText;

	LayerColor* enemyDeckCardCountFrame;
	Label* enemyDeckCardCountText;
};
