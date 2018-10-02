#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateReplaceCards : public StateBase
{
public:
	static StateReplaceCards * create();

protected:
	void beforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateReplaceCards();
	~StateReplaceCards();

	void initializePositions() override;
	void initializeListeners() override;
	void onEndReplaceCards(MenuSprite* menuSprite);
	void initializeCardReplace(GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* card);
	void removeCardsOfTypeFromDeck(Card* cardToRemove, Deck* deck);
	CallFunc* getNextStateTransition();

	std::set<Card*>* replacedCards;
	GameState* activeGameState;
	TextMenuSprite* doneButton;
};
