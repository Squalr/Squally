#include "CardRow.h"

const float CardRow::standardInsertDelay = 0.5f;

CardRow* CardRow::create()
{
	CardRow* cardRow = new CardRow();

	cardRow->autorelease();

	return cardRow;
}

CardRow::CardRow()
{
	this->mouseOverCallback = nullptr;
	this->mouseClickCallback = nullptr;

	this->rowCards = new std::set<Card*>();
}

CardRow::~CardRow()
{
	delete(this->rowCards);
}

void CardRow::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void CardRow::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CardRow::initializeListeners()
{
}

void CardRow::insertCard(Card* card, float cardInsertDelay)
{
	GameUtils::changeParent(card, this, true);

	card->setMouseOverCallback(this->mouseOverCallback);
	card->setMouseClickCallback(this->mouseClickCallback);
	card->reveal();

	this->rowCards->insert(card);
	this->setCardPositions(cardInsertDelay);
}

Card* CardRow::removeCard(Card* card)
{
	this->rowCards->erase(card);
	this->setCardPositions(CardRow::standardInsertDelay);

	// Note: We let the caller remove the child because it allows for control over positioning

	return card;
}

int CardRow::getCardCount()
{
	return this->rowCards->size();
}

void CardRow::clear()
{
	this->removeAllChildren();
	this->rowCards->clear();
}

void CardRow::setMouseOverCallback(std::function<void(Card*)> callback)
{
	this->mouseOverCallback = callback;

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseOverCallback(this->mouseOverCallback);
	}
}

void CardRow::setMouseClickCallback(std::function<void(Card*)> callback)
{
	this->mouseClickCallback = callback;

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(this->mouseClickCallback);
	}
}

void CardRow::setCardPositions(float cardRepositionDelay)
{
	int cardCount = this->rowCards->size();
	int index = 0;

	float cardWidth = 225.0f * Card::cardScale;
	float boardWidth = 992.0f;
	float spacing = 128.0f;

	// Start overlapping cards after the row fills
	if (cardCount > 8)
	{
		spacing = (boardWidth - cardWidth) / (cardCount - 1);
	}

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		float newX = (index * spacing) - (spacing * (cardCount - 1)) / 2.0f;

		if (cardRepositionDelay > 0.0f) {
			card->stopAllActions();
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
