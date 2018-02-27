#include "Deck.h"

Deck* Deck::create()
{
	Deck* deck = new Deck();

	deck->autorelease();

	return deck;
}

Deck* Deck::create(Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	Deck* deck = new Deck(cardStyle, cards);

	deck->autorelease();

	return deck;
}

Deck::Deck()
{
	this->deckCards = new std::vector<Card*>();
}

Deck::Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	this->style = cardStyle;
	this->deckCards = new std::vector<Card*>();

	for (auto it = cards->begin(); it != cards->end(); *it++)
	{
		Card* card = Card::create(this->style, *it);

		this->deckCards->push_back(card);
		this->addChild(card);
	}
}

Deck::~Deck()
{
	delete(this->deckCards);
}

void Deck::onEnter()
{
	this->initializePositions();
	this->initializeListeners();
}

void Deck::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Deck::initializeListeners()
{
}

void Deck::copyTo(Deck* otherDeck)
{
	otherDeck->clear();
	otherDeck->style = this->style;

	for (auto it = this->deckCards->begin(); it != this->deckCards->end(); *it++)
	{
		Card* card = Card::create(this->style, (*it)->cardData);

		otherDeck->deckCards->push_back(card);
		otherDeck->addChild(card);
	}
}

void Deck::clear()
{
	this->removeAllChildren();
	this->deckCards->clear();
}

Card* Deck::drawCard()
{
	Card* card = this->deckCards->back();

	this->deckCards->pop_back();

	return card;
}
