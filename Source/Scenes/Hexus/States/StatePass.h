#pragma once

#include "Scenes/Hexus/States/StateBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableIconNode;
class LocalizedLabel;
class SmartParticles;
class Sound;

class StatePass : public StateBase
{
public:
	static StatePass* create();

protected:
	StatePass();
	virtual ~StatePass();

	void onEnter() override;
	void initializePositions() override;
	
	void onAfterAnyStateChange(GameState* gameState) override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void onPassClick(GameState* gameState);
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

	ClickableNode* currentVisiblePlayerButton;
	bool playerChoiceLocked;
	bool enemyChoiceLocked;

	// We need Hexus to be able to reach in and grab a pointer to UI elements so that they can be focused by tutorials
	friend class Hexus;

	cocos2d::Sprite* lastStandSprite;
	ClickableNode* lastStandButton;
	cocos2d::LayerColor* lastStandPanel;
	LocalizedLabel* lastStandLabel;
	SmartParticles* lastStandParticles;

	cocos2d::Sprite* enemyLastStandSprite;
	SmartParticles* enemyLastStandParticles;

	// Surrender
	cocos2d::Sprite* passSprite;
	ClickableNode* passButton;
	cocos2d::LayerColor* passPanel;
	LocalizedLabel* passLabel;
	SmartParticles* passParticles;

	cocos2d::Sprite* enemyPassSprite;
	SmartParticles* enemyPassParticles;

	// Claim victory
	cocos2d::Sprite* claimVictorySprite;
	ClickableNode* claimVictoryButton;
	cocos2d::LayerColor* claimVictoryPanel;
	LocalizedLabel* claimVictoryLabel;
	SmartParticles* claimVictoryParticles;

	cocos2d::Sprite* enemyClaimVictorySprite;
	SmartParticles* enemyClaimVictoryParticles;

	Sound* passSound;
	Sound* lastStandSound;
	Sound* claimVictorySound;
};
