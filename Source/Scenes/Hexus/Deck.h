#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/Card.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class Deck : public SmartNode
{
public:
	static Deck* create();
	static Deck* create(Card::CardStyle cardStyle, std::vector<CardData*> cards);

	void copyTo(Deck* otherDeck);
	int getCardCount();

	void enableTopCardInteraction(std::function<void(Card*)> mouseOverCallback);
	void disableInteraction();
	void enableDeckSelection(std::function<void(Deck*)> callback);
	void disableDeckSelection();
	void enableClearOperationsOnInsert();
	void removeCardsWhere(std::function<bool(Card*)> predicate);
	Card* removeCard(Card* card);
	Card* drawCard();
	bool hasCards();
	void shuffle();
	void insertCardTop(Card* card, bool faceUp, float insertDelay);
	void insertCardBottom(Card* card, bool faceUp, float insertDelay);
	void insertCardRandom(Card* card, bool faceUp, float insertDelay);
	void clear();
	std::vector<Card*> deckCards;

private:
	typedef SmartNode super;
	Deck();
	Deck(Card::CardStyle cardStyle, std::vector<CardData*> cardData);
	~Deck();

	void setCardOrder();
	void doInsertAnimation(Card* card, bool faceUp, float insertDelay);

	bool clearOperationsOnInsert;
	
	ClickableNode* pad;
	cocos2d::Node* cardsNode;
	cocos2d::Sprite* deckFocus;
	Card::CardStyle style;
};
