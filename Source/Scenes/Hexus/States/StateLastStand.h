#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateLastStand : public StateBase
{
public:
	static StateLastStand * create();

protected:
	void onStateChange(GameState* gameState) override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateLastStand();
	~StateLastStand();

	void onEnter() override;
	void initializePositions() override;
	void onLastStandClick(MenuSprite* menuSprite, GameState* gameState);
	void onLastStandMouseOver(MenuSprite* menuSprite);
	void onLastStandMouseOut(MenuSprite* menuSprite);
	void enableLastStandButton(GameState* gameState);
	void disableLastStandButton();

	MenuSprite* lastStandButton;
	LayerColor* lastStandPanel;
	Label* lastStandLabel;
	Label* lastStandBonusLabel;
	ParticleSystemQuad* lastStandParticles;

	Sprite* enemyLastStandSprite;
	Label* enemyLastStandBonusLabel;
	ParticleSystemQuad* enemyLastStandParticles;

	static const std::string StringKeyHexusLastStand;
};
