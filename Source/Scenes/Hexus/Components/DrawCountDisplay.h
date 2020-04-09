#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ConstantString;
class LocalizedLabel;

class DrawCountDisplay : public ComponentBase
{
public:
	static DrawCountDisplay* create();

protected:
	DrawCountDisplay();
	virtual ~DrawCountDisplay();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void onDrawCountDisplayMouseOver();
	void onDrawCountDisplayMouseOut();
	void enableDrawCountDisplayInteraction();
	void disableDrawCountDisplayInteraction();

	ClickableNode* drawCountSprite;
	ConstantString* drawCountStr;
	LocalizedLabel* drawCountLabel;

	cocos2d::LayerColor* deckDrawCountMouseOverPanel;
	LocalizedLabel* deckDrawCountCardMouseOverLabel;

	cocos2d::Sprite* enemyDrawCountSprite;
	ConstantString* enemyDrawCountStr;
	LocalizedLabel* enemyDrawCountLabel;
};
