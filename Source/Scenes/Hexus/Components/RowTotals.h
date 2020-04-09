#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class RowTotals : public ComponentBase
{
public:
	static RowTotals* create();

	// Public so that tutorials can focus these
	cocos2d::Sprite* enemyBinaryTotalSocket;
	cocos2d::Sprite* enemyDecimalTotalSocket;
	cocos2d::Sprite* enemyHexTotalSocket;
	cocos2d::Sprite* playerBinaryTotalSocket;
	cocos2d::Sprite* playerDecimalTotalSocket;
	cocos2d::Sprite* playerHexTotalSocket;

protected:
	RowTotals();
	virtual ~RowTotals();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void readNewTotals(GameState* gameState, bool displayDeltas);
	void updateTotals(GameState* gameState);
	void runDeltaAnimation(LocalizedLabel* label, ConstantString* str, float startPositionY, int delta);

	LocalizedLabel* enemyBinaryCardTotal;
	LocalizedLabel* enemyDecimalCardTotal;
	LocalizedLabel* enemyHexCardTotal;
	LocalizedLabel* playerBinaryCardTotal;
	LocalizedLabel* playerDecimalCardTotal;
	LocalizedLabel* playerHexCardTotal;

	ConstantString* enemyBinaryCardTotalStr;
	ConstantString* enemyDecimalCardTotalStr;
	ConstantString* enemyHexCardTotalStr;
	ConstantString* playerBinaryCardTotalStr;
	ConstantString* playerDecimalCardTotalStr;
	ConstantString* playerHexCardTotalStr;

	LocalizedLabel* enemyBinaryCardIncreaseLabel;
	LocalizedLabel* enemyDecimalCardIncreaseLabel;
	LocalizedLabel* enemyHexCardIncreaseLabel;
	LocalizedLabel* playerBinaryCardIncreaseLabel;
	LocalizedLabel* playerDecimalCardIncreaseLabel;
	LocalizedLabel* playerHexCardIncreaseLabel;

	ConstantString* enemyBinaryCardIncreaseStr;
	ConstantString* enemyDecimalCardIncreaseStr;
	ConstantString* enemyHexCardIncreaseStr;
	ConstantString* playerBinaryCardIncreaseStr;
	ConstantString* playerDecimalCardIncreaseStr;
	ConstantString* playerHexCardIncreaseStr;

	LocalizedLabel* enemyBinaryCardDecreaseLabel;
	LocalizedLabel* enemyDecimalCardDecreaseLabel;
	LocalizedLabel* enemyHexCardDecreaseLabel;
	LocalizedLabel* playerBinaryCardDecreaseLabel;
	LocalizedLabel* playerDecimalCardDecreaseLabel;
	LocalizedLabel* playerHexCardDecreaseLabel;

	ConstantString* enemyBinaryCardDecreaseStr;
	ConstantString* enemyDecimalCardDecreaseStr;
	ConstantString* enemyHexCardDecreaseStr;
	ConstantString* playerBinaryCardDecreaseStr;
	ConstantString* playerDecimalCardDecreaseStr;
	ConstantString* playerHexCardDecreaseStr;

	int cachedEnemyBinaryTotal;
	int cachedEnemyDecimalTotal;
	int cachedEnemyHexTotal;
	int cachedPlayerBinaryTotal;
	int cachedPlayerDecimalTotal;
	int cachedPlayerHexTotal;

	static const int CacheCipher;
};
