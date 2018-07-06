#include "CardStorage.h"

CardStorage* CardStorage::create()
{
	CardStorage* instance = new CardStorage();

	instance->autorelease();

	return instance;
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

