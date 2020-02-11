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
class LocalizedString;
class SmartParticles;

class RemainingCardDisplay : public ComponentBase
{
public:
	static RemainingCardDisplay * create();

protected:
	RemainingCardDisplay();
	virtual ~RemainingCardDisplay();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void onRemaningCardDisplayMouseOver();
	void onRemaningCardDisplayMouseOut();
	void enableCardDisplayInteraction();
	void disableCardDisplayInteraction();

	SmartParticles* particles;

	ClickableNode* remainingCardSprite;
	ConstantString* remainingCardStr;
	LocalizedLabel* remainingCardLabel;

	cocos2d::LayerColor* remainingCardMouseOverPanel;
	LocalizedLabel* remainingCardMouseOverLabel;

	cocos2d::Sprite* enemyRemainingCardSprite;
	ConstantString* enemyRemainingCardStr;
	LocalizedLabel* enemyRemainingCardLabel;

	LocalizedString* infinityString;
};
