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
	this->deckCards = nullptr;
}

Deck::Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	this->deckCards = new std::vector<Card*>();

	for (auto it = cards->begin(); it != cards->end(); *it++)
	{
		Card* card = Card::create(Card::CardStyle::Robotic, *it);

		this->deckCards->push_back(card);
		this->addChild(card);
	}
}

Deck::~Deck()
{
	if (this->deckCards != nullptr)
	{
		delete(this->deckCards);
	}
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

void Deck::CopyDeck(Deck* deck)
{

}

Card* Deck::drawCard()
{
	Card* card = this->deckCards->back();

	this->deckCards->pop_back();

	return card;
}
