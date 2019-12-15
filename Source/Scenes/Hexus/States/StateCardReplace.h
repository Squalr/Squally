#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;
class ClickableTextNode;
class ClickableNode;
class FocusTakeOver;

class StateCardReplace : public StateBase
{
public:
	static StateCardReplace* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateCardReplace();
	~StateCardReplace();

	void onEnter() override;
	void initializePositions() override;
	void onEndReplaceCards(GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* cardToReplace, GameState* gameState);

	FocusTakeOver* focusTakeOver;
	std::vector<Card*> removedCards;
	ClickableTextNode* doneButton;
};
