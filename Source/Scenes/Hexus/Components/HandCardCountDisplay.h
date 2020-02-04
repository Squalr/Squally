#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class HandCardCountDisplay : public ComponentBase
{
public:
	static HandCardCountDisplay* create();

protected:
	HandCardCountDisplay();
	virtual ~HandCardCountDisplay();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void updateTotals(GameState* gameState);

	cocos2d::LayerColor* playerHandCardCountFrame;
	ConstantString* playerHandCardCountStr;
	LocalizedLabel* playerHandCardCountLabel;
	cocos2d::Sprite* playerHandCardIcon;

	cocos2d::LayerColor* enemyHandCardCountFrame;
	ConstantString* enemyHandCardCountStr;
	LocalizedLabel* enemyHandCardCountLabel;
	cocos2d::Sprite* enemyHandCardIcon;
};
