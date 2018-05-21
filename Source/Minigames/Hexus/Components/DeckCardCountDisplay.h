#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

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
