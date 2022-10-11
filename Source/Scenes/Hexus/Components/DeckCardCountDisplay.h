#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
}

class ConstantString;
class LocalizedLabel;

class DeckCardCountDisplay : public ComponentBase
{
public:
	static DeckCardCountDisplay* create();

protected:
	DeckCardCountDisplay();
	virtual ~DeckCardCountDisplay();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	
	void updateTotals(GameState* gameState);

	cocos2d::LayerColor* playerDeckCardCountFrame = nullptr;
	ConstantString* playerDeckCardCountStr = nullptr;
	LocalizedLabel* playerDeckCardCountLabel = nullptr;

	cocos2d::LayerColor* enemyDeckCardCountFrame = nullptr;
	ConstantString* enemyDeckCardCountStr = nullptr;
	LocalizedLabel* enemyDeckCardCountLabel = nullptr;
};
