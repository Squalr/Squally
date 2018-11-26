#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/IconMenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StatePass : public StateBase
{
public:
	static StatePass * create();

	// Note: These are public so that tutorials can access them for focus
	// Last stand
	Sprite* lastStandSprite;
	IconMenuSprite* lastStandButton;
	LayerColor* lastStandPanel;
	Label* lastStandLabel;
	ParticleSystemQuad* lastStandParticles;

	Sprite* enemyLastStandSprite;
	ParticleSystemQuad* enemyLastStandParticles;

	// Surrender
	Sprite* passSprite;
	IconMenuSprite* passButton;
	LayerColor* passPanel;
	Label* passLabel;
	ParticleSystemQuad* passParticles;

	Sprite* enemyPassSprite;
	ParticleSystemQuad* enemyPassParticles;

	// Claim victory
	Sprite* claimVictorySprite;
	IconMenuSprite* claimVictoryButton;
	LayerColor* claimVictoryPanel;
	Label* claimVictoryLabel;
	ParticleSystemQuad* claimVictoryParticles;

	Sprite* enemyClaimVictorySprite;
	ParticleSystemQuad* enemyClaimVictoryParticles;

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
	void onPassClick(MenuSprite* menuSprite, GameState* gameState);
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

	IconMenuSprite* currentVisiblePlayerButton;
	bool playerChoiceLocked;
	bool enemyChoiceLocked;

	static const std::string StringKeyHexusPass;
	static const std::string StringKeyHexusLastStand;
	static const std::string StringKeyHexusClaimVictory;
};
