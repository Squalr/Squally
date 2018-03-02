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
	GameUtils::changeParent(card, this, true);

	card->reveal();

	this->handCards->push_back(card);
	this->setCardPositions(cardInsertDelay);
}

int Hand::getCardCount()
{
	return this->handCards->size();
}

void Hand::clear()
{
	this->removeAllChildren();
	this->handCards->clear();
}

void Hand::setCardPositions(float cardRepositionDelay)
{
	int cardCount = this->handCards->size();
	int index = 0;

	float cardWidth = 225.0f * Card::cardScale;
	float boardWidth = 992.0f;
	float spacing = 128.0f;

	// Start overlapping cards after the row fills
	if (cardCount > 8)
	{
		spacing = (boardWidth - cardWidth) / (cardCount - 1);
	}


	for (auto it = this->handCards->begin(); it != this->handCards->end(); it++)
	{
		Card* card = *it;

		float newX = (index * spacing) - (spacing * (cardCount - 1)) / 2.0f;

		if (cardRepositionDelay > 0.0f) {
			card->runAction(EaseSineInOut::create(MoveTo::create(cardRepositionDelay, Vec2(newX, 0.0f))));
			card->runAction(ScaleTo::create(cardRepositionDelay, Card::cardScale));
		}
		else {
			card->setPosition(Vec2(newX, 0.0f));
			card->setScale(Card::cardScale);
		}
		index++;
	}
}
