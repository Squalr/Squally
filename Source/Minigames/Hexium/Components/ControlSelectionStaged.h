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
	void selectCard(Card* card);
	void playSelectedCard(CardRow* cardRow);

	GameState* activeGameState;
};
