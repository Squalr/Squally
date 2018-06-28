#include "CardRow.h"

CardRow* CardRow::create()
{
	CardRow* instance = new CardRow();

	instance->autorelease();

	return instance;
}

CardRow::CardRow()
{
	this->rowCards = new std::vector<Card*>();
	this->rowSelectCallback = nullptr;
	this->rowWidth = Config::rowWidth;

	this->rowSelectSprite = MenuSprite::create(Resources::Minigames_Hexus_RowSelection, Resources::Minigames_Hexus_RowSelectionHighlight, Resources::Minigames_Hexus_RowSelectionHighlight);

	this->rowSelectSprite->setOpacity(0);
	this->rowSelectSprite->setVisible(false);

	this->setCardScale(Card::cardScale, 0.0f);

	this->addChild(this->rowSelectSprite);
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
}

void CardRow::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->rowSelectSprite->setClickCallback(CC_CALLBACK_1(CardRow::onRowSelectClick, this));
}

void CardRow::setRowWidth(float newRowWidth, float duration)
{
	this->rowWidth = newRowWidth;

	this->setCardPositions(duration);
}

void CardRow::setCardScale(float scale, float scaleSpeed)
{
	this->cardScale = scale;

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		if (scaleSpeed > 0.0f) {
			card->stopAllActions();
			card->runAction(ScaleTo::create(scaleSpeed , this->cardScale));
		}
		else {
			card->setPosition(card->position);
			card->setScale(this->cardScale);
		}
	}
}

float CardRow::getCardScale()
{
	return this->cardScale;
}

void CardRow::insertCard(Card* card, float cardInsertDelay)
{
	GameUtils::changeParent(card, this, true);

	card->setMouseOverCallback(nullptr);
	card->setMouseClickCallback(nullptr);
	card->reveal();

	this->rowCards->push_back(card);
	this->setCardPositions(cardInsertDelay);
}

Card* CardRow::removeCard(Card* card)
{
	this->rowCards->erase(std::remove(this->rowCards->begin(), this->rowCards->end(), card), this->rowCards->end());
	this->setCardPositions(Config::insertDelay);

	// Note: We let the caller remove the child because it allows for control over positioning

	return card;
}

int CardRow::getCardCount()
{
	return this->rowCards->size();
}

int CardRow::getRowAttack()
{
	int attack = 0;

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		attack += card->getAttack();
	}

	return attack;
}

void CardRow::enableRowSelection(std::function<void(CardRow*)> callback)
{
	this->rowSelectCallback = callback;

	this->rowSelectSprite->stopAllActions();

	this->rowSelectSprite->setVisible(true);
	this->rowSelectSprite->stopAllActions();

	this->rowSelectSprite->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		nullptr));

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->disableInteraction();
	}
}

void CardRow::enableRowCardSelection(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(callback);
		card->focus();
	}
}

void CardRow::disableRowSelection()
{
	this->rowSelectCallback = nullptr;

	MenuSprite* sprite = this->rowSelectSprite;

	this->rowSelectSprite->stopAllActions();
	this->rowSelectSprite->runAction(Sequence::create(
		FadeTo::create(0.25f, 0),
		CallFunc::create([sprite]
	{
		sprite->setVisible(false);
	}),
		nullptr));

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->enableInteraction();
	}
}

void CardRow::disableRowCardSelection()
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(nullptr);
		card->unfocus();
	}
}

void CardRow::clear()
{
	this->removeAllChildren();
	this->rowCards->clear();
}

void CardRow::setMouseOverCallback(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseOverCallback(callback);
	}
}

void CardRow::setMouseClickCallback(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(callback);
	}
}

void CardRow::setCardPositions(float cardRepositionDelay)
{
	int cardCount = this->rowCards->size();
	int index = 0;

	float cardWidth = 225.0f * this->cardScale;
	float spacing = Config::defaultCardSpacing;

	// Start overlapping cards after the row fills
	if (cardCount > 7)
	{
		spacing = (this->rowWidth - cardWidth) / (cardCount - 1);
	}

	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		float newX = (index * spacing) - (spacing * (cardCount - 1)) / 2.0f;

		card->position = Vec2(newX, 0.0f);

		if (cardRepositionDelay > 0.0f) {
			card->stopAllActions();
			card->runAction(EaseSineInOut::create(MoveTo::create(cardRepositionDelay, card->position)));
			card->runAction(ScaleTo::create(cardRepositionDelay, this->cardScale));
		}
		else {
			card->setPosition(card->position);
			card->setScale(this->cardScale);
		}

		index++;
	}
}

void CardRow::onRowSelectClick(MenuSprite* menuSprite)
{
	if (this->rowSelectCallback != nullptr)
	{
		this->rowSelectCallback(this);
	}
}
