#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class ControlSelectionStaged : public ComponentBase
{
public:
	static ControlSelectionStaged * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlSelectionStaged();
	~ControlSelectionStaged();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageSelectedSacrificeCard(Card* card);
	void playSelectedCard(CardRow* cardRow);
	void updateSelectionStatus();
	void onSelectionCancel(MenuSprite* menuSprite);

	GameState* activeGameState;
	Label* selectionLabel;
	MenuSprite* cancelButton;
};
