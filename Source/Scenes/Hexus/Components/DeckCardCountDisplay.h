#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

using namespace cocos2d;

class DeckCardCountDisplay : public ComponentBase
{
public:
	static DeckCardCountDisplay * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	DeckCardCountDisplay();
	~DeckCardCountDisplay();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void updateTotals(GameState* gameState);

	LayerColor* playerDeckCardCountFrame;
	Label* playerDeckCardCountText;

	LayerColor* enemyDeckCardCountFrame;
	Label* enemyDeckCardCountText;
};
