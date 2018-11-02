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
	void initializeSelectablesAndCallbacks(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageSelectedCombineCard(Card* card, GameState* gameState);
	void onRowChosen(CardRow* cardRow, GameState* gameState);
	void updateSelectionStatus(GameState* gameState);
	void onSelectionCancel(MenuSprite* menuSprite, GameState* gameState);
	void onHelpClick(MenuSprite* menuSprite, GameState* gameState);
	void clearSelectionStatus();

	Label* selectionLabel;
	MenuSprite* cancelButton;
	MenuSprite* helpButton;
};
