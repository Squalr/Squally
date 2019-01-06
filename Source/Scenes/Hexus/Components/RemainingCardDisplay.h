#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class ParticleSystemQuad;
	class Sprite;
}

class LocalizedLabel;
class ClickableNode;

class RemainingCardDisplay : public ComponentBase
{
public:
	static RemainingCardDisplay * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
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
	LocalizedLabel* remainingCardLabel;

	cocos2d::LayerColor* remainingCardMouseOverPanel;
	LocalizedLabel* remainingCardMouseOverLabel;

	cocos2d::Sprite* enemyRemainingCardSprite;
	LocalizedLabel* enemyRemainingCardLabel;
};
