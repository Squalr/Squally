#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateSacrificeStaged : public StateBase
{
public:
	static StateSacrificeStaged * create();

protected:
	void beforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateSacrificeStaged();
	~StateSacrificeStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageSacrificeTarget(Card* card);
	void updateSacrificeStatus();
	void onSacrificeCancel(MenuSprite* menuSprite);

	GameState* activeGameState;
	Label* sacrificeStatus;
	MenuSprite* cancelButton;
};
