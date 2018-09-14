#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Card.h"

using namespace cocos2d;

class Deck : public SmartNode
{
public:
	static Deck * create();
	static Deck * create(Card::CardStyle cardStyle, std::vector<CardData*>* cards);

	void copyTo(Deck* otherDeck);
	int getCardCount();

	Card* drawCard();
	bool hasCards();
	void insertCardTop(Card* card, bool faceUp, float insertDelay);
	void insertCardBottom(Card* card, bool faceUp, float insertDelay);
	void insertCardRandom(Card* card, bool faceUp, float insertDelay);
	void clear();

private:
	Deck();
	Deck(Card::CardStyle cardStyle, std::vector<Card*>* cards);
	Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards);
	~Deck();

	void setCardOrder();
	void doInsertAnimation(Card* card, bool faceUp, float insertDelay);

	Sprite* pad;
	Card::CardStyle style;
	std::vector<Card*>* deckCards;
};

