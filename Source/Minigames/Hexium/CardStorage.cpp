#include "CardStorage.h"

CardStorage* CardStorage::create()
{
	CardStorage* hand = new CardStorage();

	hand->autorelease();

	return hand;
}

CardStorage::CardStorage()
{
	this->initializePositions();
	this->initializeListeners();
}

CardStorage::~CardStorage()
{
}

void CardStorage::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CardStorage::initializeListeners()
{
}

