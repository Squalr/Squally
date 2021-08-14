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
	cocos2d::Sprite* enemyBinaryTotalSocket = nullptr;
	cocos2d::Sprite* enemyDecimalTotalSocket = nullptr;
	cocos2d::Sprite* enemyHexTotalSocket = nullptr;
	cocos2d::Sprite* playerBinaryTotalSocket = nullptr;
	cocos2d::Sprite* playerDecimalTotalSocket = nullptr;
	cocos2d::Sprite* playerHexTotalSocket = nullptr;

protected:
	RowTotals();
	virtual ~RowTotals();

	void onEnter() override;
	void initializePositions() override;
	void onAfterAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	
	void readNewTotals(GameState* gameState, bool displayDeltas);
	void updateTotals(GameState* gameState);
	void runDeltaAnimation(LocalizedLabel* label, ConstantString* str, float startPositionY, int delta);

	LocalizedLabel* enemyBinaryCardTotal = nullptr;
	LocalizedLabel* enemyDecimalCardTotal = nullptr;
	LocalizedLabel* enemyHexCardTotal = nullptr;
	LocalizedLabel* playerBinaryCardTotal = nullptr;
	LocalizedLabel* playerDecimalCardTotal = nullptr;
	LocalizedLabel* playerHexCardTotal = nullptr;

	ConstantString* enemyBinaryCardTotalStr = nullptr;
	ConstantString* enemyDecimalCardTotalStr = nullptr;
	ConstantString* enemyHexCardTotalStr = nullptr;
	ConstantString* playerBinaryCardTotalStr = nullptr;
	ConstantString* playerDecimalCardTotalStr = nullptr;
	ConstantString* playerHexCardTotalStr = nullptr;

	LocalizedLabel* enemyBinaryCardIncreaseLabel = nullptr;
	LocalizedLabel* enemyDecimalCardIncreaseLabel = nullptr;
	LocalizedLabel* enemyHexCardIncreaseLabel = nullptr;
	LocalizedLabel* playerBinaryCardIncreaseLabel = nullptr;
	LocalizedLabel* playerDecimalCardIncreaseLabel = nullptr;
	LocalizedLabel* playerHexCardIncreaseLabel = nullptr;

	ConstantString* enemyBinaryCardIncreaseStr = nullptr;
	ConstantString* enemyDecimalCardIncreaseStr = nullptr;
	ConstantString* enemyHexCardIncreaseStr = nullptr;
	ConstantString* playerBinaryCardIncreaseStr = nullptr;
	ConstantString* playerDecimalCardIncreaseStr = nullptr;
	ConstantString* playerHexCardIncreaseStr = nullptr;

	LocalizedLabel* enemyBinaryCardDecreaseLabel = nullptr;
	LocalizedLabel* enemyDecimalCardDecreaseLabel = nullptr;
	LocalizedLabel* enemyHexCardDecreaseLabel = nullptr;
	LocalizedLabel* playerBinaryCardDecreaseLabel = nullptr;
	LocalizedLabel* playerDecimalCardDecreaseLabel = nullptr;
	LocalizedLabel* playerHexCardDecreaseLabel = nullptr;

	ConstantString* enemyBinaryCardDecreaseStr = nullptr;
	ConstantString* enemyDecimalCardDecreaseStr = nullptr;
	ConstantString* enemyHexCardDecreaseStr = nullptr;
	ConstantString* playerBinaryCardDecreaseStr = nullptr;
	ConstantString* playerDecimalCardDecreaseStr = nullptr;
	ConstantString* playerHexCardDecreaseStr = nullptr;

	int cachedEnemyBinaryTotal = 0;
	int cachedEnemyDecimalTotal = 0;
	int cachedEnemyHexTotal = 0;
	int cachedPlayerBinaryTotal = 0;
	int cachedPlayerDecimalTotal = 0;
	int cachedPlayerHexTotal = 0;

	static const int CacheCipher;
};
