#pragma once
#include <vector>

#include "Scenes/Hexus/States/StateBase.h"

class Card;

class StateAIDecideCardReplace : public StateBase
{
public:
	static StateAIDecideCardReplace* create();

protected:
	StateAIDecideCardReplace();
	virtual ~StateAIDecideCardReplace();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void replaceCard(Card* card, GameState* gameState);

	std::vector<Card*> removedCards;
};
