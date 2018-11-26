#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class RowTotals : public ComponentBase
{
public:
	static RowTotals * create();

	// Public so that tutorials can focus these
	Sprite* enemyBinaryTotalSocket;
	Sprite* enemyDecimalTotalSocket;
	Sprite* enemyHexTotalSocket;
	Sprite* playerBinaryTotalSocket;
	Sprite* playerDecimalTotalSocket;
	Sprite* playerHexTotalSocket;

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	RowTotals();
	~RowTotals();

	void onEnter() override;
	void initializePositions() override;
	void readNewTotals(GameState* gameState, bool displayDeltas);
	void updateTotals(GameState* gameState);
	void runDeltaAnimation(Label* label, float startPositionY, int delta);

	Label* enemyBinaryCardTotal;
	Label* enemyDecimalCardTotal;
	Label* enemyHexCardTotal;
	Label* playerBinaryCardTotal;
	Label* playerDecimalCardTotal;
	Label* playerHexCardTotal;

	Label* enemyBinaryCardDeltaLabel;
	Label* enemyDecimalCardDeltaLabel;
	Label* enemyHexCardDeltaLabel;
	Label* playerBinaryCardDeltaLabel;
	Label* playerDecimalCardDeltaLabel;
	Label* playerHexCardDeltaLabel;

	int cachedEnemyBinaryTotal;
	int cachedEnemyDecimalTotal;
	int cachedEnemyHexTotal;
	int cachedPlayerBinaryTotal;
	int cachedPlayerDecimalTotal;
	int cachedPlayerHexTotal;

	static const int cacheCipher;
};
