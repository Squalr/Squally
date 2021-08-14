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
	static RemainingCardDisplay* create();

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

	SmartParticles* particles = nullptr;

	ClickableNode* remainingCardSprite = nullptr;
	ConstantString* remainingCardStr = nullptr;
	LocalizedLabel* remainingCardLabel = nullptr;

	cocos2d::LayerColor* remainingCardMouseOverPanel = nullptr;
	LocalizedLabel* remainingCardMouseOverLabel = nullptr;

	cocos2d::Sprite* enemyRemainingCardSprite = nullptr;
	ConstantString* enemyRemainingCardStr = nullptr;
	LocalizedLabel* enemyRemainingCardLabel = nullptr;

	LocalizedString* infinityString = nullptr;
};
