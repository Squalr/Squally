#include "Hand.h"

Hand* Hand::create()
{
	Hand* hand = new Hand();

	hand->autorelease();

	return hand;
}

Hand::Hand()
{
	this->handCards = new std::vector<Card*>();
}

Hand::~Hand()
{
	delete(this->handCards);
}

void Hand::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void Hand::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Hand::initializeListeners()
{
}

void Hand::insertCard(Card* card, float cardInsertDelay)
{
	GameUtils::changeParent(card, this, false);

	this->handCards->push_back(card);
}

void Hand::clear()
{

}