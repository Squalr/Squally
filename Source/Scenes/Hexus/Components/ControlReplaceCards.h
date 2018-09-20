#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ControlReplaceCards : public ComponentBase
{
public:
	static ControlReplaceCards * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlReplaceCards();
	~ControlReplaceCards();

	void initializePositions() override;
	void initializeCardReplace(GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* card);
	void removeCardsOfTypeFromDeck(Card* cardToRemove, Deck* deck);
	CallFunc* getNextStateTransition();

	std::set<Card*>* replacedCards;
	GameState* activeGameState;
};
