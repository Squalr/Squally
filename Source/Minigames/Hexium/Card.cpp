#include "Card.h"

Card* Card::create()
{
	Card* card = new Card();

	card->autorelease();

	return card;
}

Card::Card()
{
	this->initializePositions();
	this->initializeListeners();
}

Card::~Card()
{
}

void Card::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Card::initializeListeners()
{
}

void Card::reveal()
{

}

void Card::hide()
{

}
