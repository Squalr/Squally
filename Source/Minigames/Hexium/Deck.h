#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"

using namespace cocos2d;

class Deck : public Node
{
public:
	static Deck * create();
	static Deck * create(Card::CardStyle cardStyle, std::vector<CardData*>* cards);

	void copyTo(Deck* otherDeck);

	Card* drawCard();
	void clear();

private:
	Deck();
	Deck(Card::CardStyle cardStyle, std::vector<Card*>* cards);
	Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards);
	~Deck();
	void onEnter() override;

	Card::CardStyle style;
	std::vector<Card*>* deckCards;

	void initializePositions();
	void initializeListeners();
};

