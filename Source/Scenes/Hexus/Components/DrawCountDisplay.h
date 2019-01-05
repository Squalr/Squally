#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class LocalizedLabel;
class ClickableNode;

class DrawCountDisplay : public ComponentBase
{
public:
	static DrawCountDisplay* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DrawCountDisplay();
	~DrawCountDisplay();

	void onEnter() override;
	void initializePositions() override;
	void onDrawCountDisplayMouseOver();
	void onDrawCountDisplayMouseOut();
	void enableDrawCountDisplayInteraction();
	void disableDrawCountDisplayInteraction();

	ClickableNode* drawCountSprite;
	LocalizedLabel* drawCountLabel;

	cocos2d::LayerColor* deckDrawCountMouseOverPanel;
	LocalizedLabel* deckDrawCountCardMouseOverLabel;

	cocos2d::Sprite* enemyDrawCountSprite;
	LocalizedLabel* enemyDrawCountLabel;
};
