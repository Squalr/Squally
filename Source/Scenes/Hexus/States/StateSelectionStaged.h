#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateSelectionStaged : public StateBase
{
public:
	static StateSelectionStaged * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateSelectionStaged();
	~StateSelectionStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageSelectedSacrificeCard(Card* card);
	void stageSelectedCombineCard(Card* card);
	void playSelectedCard(CardRow* cardRow);
	void updateSelectionStatus();
	void onSelectionCancel(MenuSprite* menuSprite);
	void onHelpClick(MenuSprite* menuSprite);
	void clearSelectionStatus();

	GameState* activeGameState;
	Label* selectionLabel;
	MenuSprite* cancelButton;
	MenuSprite* helpButton;
};
