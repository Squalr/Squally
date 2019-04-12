#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
}

class LocalizedLabel;

class DeckCardCountDisplay : public ComponentBase
{
public:
	static DeckCardCountDisplay* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	DeckCardCountDisplay();
	~DeckCardCountDisplay();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	cocos2d::LayerColor* playerDeckCardCountFrame;
	LocalizedLabel* playerDeckCardCountText;

	cocos2d::LayerColor* enemyDeckCardCountFrame;
	LocalizedLabel* enemyDeckCardCountText;
};
