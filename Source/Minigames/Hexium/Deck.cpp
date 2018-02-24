#include "Deck.h"

Deck* Deck::create()
{
	Deck* deck = new Deck();

	deck->autorelease();

	return deck;
}

Deck::Deck()
{
	this->initializePositions();
	this->initializeListeners();
}

Deck::~Deck()
{
}

void Deck::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Deck::initializeListeners()
{
}

Card* Deck::drawCard()
{
	return nullptr;
}
