#include "Hand.h"

Hand* Hand::create()
{
	Hand* hand = new Hand();

	hand->autorelease();

	return hand;
}

Hand::Hand()
{
	this->initializePositions();
	this->initializeListeners();
}

Hand::~Hand()
{
}

void Hand::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Hand::initializeListeners()
{
}

void Hand::insertCard(Card* card)
{

}

void Hand::clear()
{

}