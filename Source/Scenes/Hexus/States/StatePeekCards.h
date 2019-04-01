#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;
class ClickableTextNode;
class ClickableNode;

class StatePeekCards : public StateBase
{
public:
	static StatePeekCards* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StatePeekCards();
	~StatePeekCards();

	void onEnter() override;
	void initializePositions() override;
	void onEndPeekCards(GameState* gameState);
	void initializeCallbacks(GameState* gameState);

	std::vector<Card*> removedCards;
	ClickableTextNode* doneButton;
};
