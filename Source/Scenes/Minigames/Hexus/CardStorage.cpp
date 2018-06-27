#include "CardStorage.h"

CardStorage* CardStorage::create()
{
	CardStorage* cardStorage = new CardStorage();

	cardStorage->autorelease();

	return cardStorage;
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
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

