#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StatePass : public StateBase
{
public:
	static StatePass * create();

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

	// Last stand
	MenuSprite* lastStandButton;
	LayerColor* lastStandPanel;
	Label* lastStandLabel;
	ParticleSystemQuad* lastStandParticles;

	Sprite* enemyLastStandSprite;
	ParticleSystemQuad* enemyLastStandParticles;

	// Surrender
	MenuSprite* passButton;
	LayerColor* passPanel;
	Label* passLabel;
	ParticleSystemQuad* passParticles;

	Sprite* enemyPassSprite;
	ParticleSystemQuad* enemyPassParticles;

	// Claim victory
	MenuSprite* claimVictoryButton;
	LayerColor* claimVictoryPanel;
	Label* claimVictoryLabel;
	ParticleSystemQuad* claimVictoryParticles;

	Sprite* enemyClaimVictorySprite;
	ParticleSystemQuad* enemyClaimVictoryParticles;

	MenuSprite* playerActivatedSprite;
	MenuSprite* opponentActivatedSprite;

	static const std::string StringKeyHexusPass;
	static const std::string StringKeyHexusLastStand;
	static const std::string StringKeyHexusClaimVictory;
};
