#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;
class TextMenuSprite;
class MenuSprite;

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
	StateCardReplace();
	~StateCardReplace();

	void onEnter() override;
	void initializePositions() override;
	void onEndReplaceCards(MenuSprite* menuSprite, GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* cardToReplace, GameState* gameState);

	std::vector<Card*> removedCards;
	TextMenuSprite* doneButton;
};
