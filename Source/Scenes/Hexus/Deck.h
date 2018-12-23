#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/Card.h"

namespace cocos2d
{
	class Sprite;
}

class Deck : public SmartNode
{
public:
	static Deck* create();
	static Deck* create(Card::CardStyle cardStyle, std::vector<CardData*> cards);

	void copyTo(Deck* otherDeck);
	int getCardCount();

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
	Deck();
	Deck(Card::CardStyle cardStyle, std::vector<CardData*> cardData);
	~Deck();

	void setCardOrder();
	void doInsertAnimation(Card* card, bool faceUp, float insertDelay);

	cocos2d::Sprite* pad;
	Card::CardStyle style;
};
