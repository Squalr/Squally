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

	void CopyDeck(Deck* deck);
	Card* drawCard();

private:
	Deck();
	Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards);
	~Deck();
	void onEnter() override;

	std::vector<Card*>* deckCards;

	void initializePositions();
	void initializeListeners();
};

