#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class LocalizedLabel;

class HandCardCountDisplay : public ComponentBase
{
public:
	static HandCardCountDisplay* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	HandCardCountDisplay();
	~HandCardCountDisplay();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	cocos2d::LayerColor* playerHandCardCountFrame;
	LocalizedLabel* playerHandCardCountText;
	cocos2d::Sprite* playerHandCardIcon;

	cocos2d::LayerColor* enemyHandCardCountFrame;
	LocalizedLabel* enemyHandCardCountText;
	cocos2d::Sprite* enemyHandCardIcon;
};
