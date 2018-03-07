#include "CardRow.h"

CardRow* CardRow::create()
{
	CardRow* cardRow = new CardRow();

	cardRow->autorelease();

	return cardRow;
}

CardRow::CardRow()
{
	this->rowCards = new std::vector<Card*>();
	this->mouseOverCallback = nullptr;
	this->mouseClickCallback = nullptr;
	this->rowSelectCallback = nullptr;
	this->rowWidth = Config::rowWidth;

	this->rowSelectSprite = MenuSprite::create(Resources::Minigames_Hexium_RowSelection, Resources::Minigames_Hexium_RowSelectionHighlight, Resources::Minigames_Hexium_RowSelectionHighlight);

	this->rowSelectSprite->setOpacity(0);
	this->rowSelectSprite->setVisible(false);

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
	this->rowSelectSprite->setClickCallback(CC_CALLBACK_1(CardRow::onRowSelectClick, this));
}

void CardRow::disableInteraction()
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(nullptr);
	}
}

void CardRow::enableInteraction()
{
	for (auto it = this->rowCards->begin(); it != this->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(this->mouseClickCallback);
	}
}

void CardRow::setRowWidth(float newRowWidth)
{
	this->rowWidth = newRowWidth;
}

void CardRow::insertCard(Card* card, float cardInsertDelay)
{
	GameUtils::changeParent(card, this, true);

	card->setMouseOverCallback(this->mouseOverCallback);
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
}

void CardRow::setCardPositions(float cardRepositionDelay)
{
	int cardCount = this->rowCards->size();
	int index = 0;

	float cardWidth = 225.0f * Card::cardScale;
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
			card->runAction(ScaleTo::create(cardRepositionDelay, Card::cardScale));
		}
		else {
			card->setPosition(card->position);
			card->setScale(Card::cardScale);
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
