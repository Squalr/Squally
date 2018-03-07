#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class RowTotals : public ComponentBase
{
public:
	static RowTotals * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	RowTotals();
	~RowTotals();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void updateTotals(GameState* gameState);

	Label* enemyBinaryCardTotal;
	Label* enemyDecimalCardTotal;
	Label* enemyHexCardTotal;
	Label* playerBinaryCardTotal;
	Label* playerDecimalCardTotal;
	Label* playerHexCardTotal;
};
