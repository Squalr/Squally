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
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DeckCardCountDisplay();
	~DeckCardCountDisplay();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	cocos2d::LayerColor* playerDeckCardCountFrame;
	LocalizedLabel* playerDeckCardCountText;

	cocos2d::LayerColor* enemyDeckCardCountFrame;
	LocalizedLabel* enemyDeckCardCountText;
};
