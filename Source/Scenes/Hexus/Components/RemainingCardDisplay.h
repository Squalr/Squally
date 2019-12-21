#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class ParticleSystemQuad;
	class Sprite;
}

class ClickableNode;
class ConstantString;
class LocalizedLabel;
class LocalizedString;

class RemainingCardDisplay : public ComponentBase
{
public:
	static RemainingCardDisplay * create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	RemainingCardDisplay();
	~RemainingCardDisplay();

	void onEnter() override;
	void initializePositions() override;
	void onRemaningCardDisplayMouseOver();
	void onRemaningCardDisplayMouseOut();
	void enableCardDisplayInteraction();
	void disableCardDisplayInteraction();

	cocos2d::ParticleSystemQuad* particles;

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
