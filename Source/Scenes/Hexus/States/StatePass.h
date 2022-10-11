#pragma once

#include "Scenes/Hexus/States/StateBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
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

	ClickableNode* currentVisiblePlayerButton = nullptr;
	bool playerChoiceLocked = false;
	bool enemyChoiceLocked = false;

	// We need Hexus to be able to reach in and grab a pointer to UI elements so that they can be focused by tutorials
	friend class Hexus;

	cocos2d::Sprite* lastStandSprite = nullptr;
	ClickableNode* lastStandButton = nullptr;
	cocos2d::LayerColor* lastStandPanel = nullptr;
	LocalizedLabel* lastStandLabel = nullptr;
	SmartParticles* lastStandParticles = nullptr;

	cocos2d::Sprite* enemyLastStandSprite = nullptr;
	SmartParticles* enemyLastStandParticles = nullptr;

	// Surrender
	cocos2d::Sprite* passSprite = nullptr;
	ClickableNode* passButton = nullptr;
	cocos2d::LayerColor* passPanel = nullptr;
	LocalizedLabel* passLabel = nullptr;
	SmartParticles* passParticles = nullptr;

	cocos2d::Sprite* enemyPassSprite = nullptr;
	SmartParticles* enemyPassParticles = nullptr;

	// Claim victory
	cocos2d::Sprite* claimVictorySprite = nullptr;
	ClickableNode* claimVictoryButton = nullptr;
	cocos2d::LayerColor* claimVictoryPanel = nullptr;
	LocalizedLabel* claimVictoryLabel = nullptr;
	SmartParticles* claimVictoryParticles = nullptr;

	cocos2d::Sprite* enemyClaimVictorySprite = nullptr;
	SmartParticles* enemyClaimVictoryParticles = nullptr;

	Sound* passSound = nullptr;
	Sound* lastStandSound = nullptr;
	Sound* claimVictorySound = nullptr;
};
