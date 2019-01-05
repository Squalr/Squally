#pragma once

#include "Scenes/Hexus/States/StateBase.h"

namespace cocos2d
{
	class LayerColor;
	class ParticleSystemQuad;
	class Sprite;
}

class ClickableIconNode;
class LocalizedLabel;
class ClickableNode;

class StatePass : public StateBase
{
public:
	static StatePass* create();

protected:
	void onAnyStateChange(GameState* gameState) override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StatePass();
	~StatePass();

	void onEnter() override;
	void initializePositions() override;
	void onPassClick(ClickableNode* menuSprite, GameState* gameState);
	void hideOpponenentPassSprites();
	void hideAndDisableAllButtons();
	void enablePassButtonInteraction(GameState* gameState);
	void enableLastStandButtonInteraction(GameState* gameState);
	void enableClaimVictoryButtonInteraction(GameState* gameState);
	void showPassButton();
	void showLastStandButton();
	void showClaimVictoryButton();
	void onPassMouseOver();
	void onPassMouseOut();
	void onLastStandMouseOver();
	void onLastStandMouseOut();
	void onClaimVictoryMouseOver();
	void onClaimVictoryMouseOut();

	ClickableIconNode* currentVisiblePlayerButton;
	bool playerChoiceLocked;
	bool enemyChoiceLocked;

	// We need Hexus to be able to reach in and grab a pointer to UI elements so that they can be focused by tutorials
	friend class Hexus;

	cocos2d::Sprite* lastStandSprite;
	ClickableIconNode* lastStandButton;
	cocos2d::LayerColor* lastStandPanel;
	LocalizedLabel* lastStandLabel;
	cocos2d::ParticleSystemQuad* lastStandParticles;

	cocos2d::Sprite* enemyLastStandSprite;
	cocos2d::ParticleSystemQuad* enemyLastStandParticles;

	// Surrender
	cocos2d::Sprite* passSprite;
	ClickableIconNode* passButton;
	cocos2d::LayerColor* passPanel;
	LocalizedLabel* passLabel;
	cocos2d::ParticleSystemQuad* passParticles;

	cocos2d::Sprite* enemyPassSprite;
	cocos2d::ParticleSystemQuad* enemyPassParticles;

	// Claim victory
	cocos2d::Sprite* claimVictorySprite;
	ClickableIconNode* claimVictoryButton;
	cocos2d::LayerColor* claimVictoryPanel;
	LocalizedLabel* claimVictoryLabel;
	cocos2d::ParticleSystemQuad* claimVictoryParticles;

	cocos2d::Sprite* enemyClaimVictorySprite;
	cocos2d::ParticleSystemQuad* enemyClaimVictoryParticles;
};
