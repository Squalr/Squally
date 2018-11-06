#include "CardRow.h"

CardRow* CardRow::create(bool isPlayerRow)
{
    CardRow * instance = new (std::nothrow) CardRow(isPlayerRow);

    if (instance && instance->init())
    {
        instance->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(instance);
    }

    return instance;
}

CardRow::CardRow(bool isPlayerRow)
{
	this->belongsToPlayer = isPlayerRow;
	this->rowCards = std::vector<Card*>();
	this->rowSelectCallback = nullptr;
	this->rowWidth = Config::rowWidth;

	this->rowSelectSprite = MenuSprite::create(Resources::Minigames_Hexus_RowSelection, Resources::Minigames_Hexus_RowSelectionHighlight);
	this->rowSelectSprite->setOpacity(0);
	this->rowSelectSprite->setVisible(false);
	this->setCardScale(Card::cardScale, 0.0f);

	this->addChild(this->rowSelectSprite);
}

CardRow::~CardRow()
{
}

void CardRow::initializeListeners()
{
	SmartNode::initializeListeners();
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

	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
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

void CardRow::insertCards(std::vector<Card*> cards, float cardInsertDelay, float indexDelay)
{
	for (auto it = cards.begin(); it != cards.end(); it++)
	{
		Card* card = *it;

		if (card == nullptr)
		{
			return;
		}

		GameUtils::changeParent(card, this, true);

		card->setMouseOverCallback(nullptr);
		card->setMouseClickCallback(nullptr);
		card->reveal();

		this->rowCards.push_back(card);
	}

	this->setCardPositions(cardInsertDelay, indexDelay);
}

void CardRow::insertCard(Card* card, float cardInsertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	GameUtils::changeParent(card, this, true);

	card->setMouseOverCallback(nullptr);
	card->setMouseClickCallback(nullptr);
	card->reveal();

	this->rowCards.push_back(card);
	this->setCardPositions(cardInsertDelay);
}

Card* CardRow::removeCard(Card* card)
{
	if (std::find(this->rowCards.begin(), this->rowCards.end(), card) == this->rowCards.end())
	{
		// Not found
		return nullptr;
	}

	this->rowCards.erase(std::remove(this->rowCards.begin(), this->rowCards.end(), card), this->rowCards.end());
	this->setCardPositions(Config::insertDelay);

	return card; // Note: We let the caller remove the child because it allows for control over positioning
}

int CardRow::getCardCount()
{
	return this->rowCards.size();
}

int CardRow::getRowAttack()
{
	int attack = 0;

	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
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

	// Disable card interactions because the player is interacting with the whole row
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->disableInteraction();
	}
}

void CardRow::enableRowCardSelection(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
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
	this->rowSelectSprite->runAction(Sequence::create(FadeTo::create(0.25f, 0), CallFunc::create([sprite]{
		sprite->setVisible(false);
	}), nullptr));

	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->enableInteraction();
	}
}

void CardRow::disableRowCardSelection()
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;

		card->setMouseClickCallback(nullptr);
		card->unfocus();
	}
}

// TODO, SPLIT OFF methods for hand into seperate class, Card Row on the field is very different than card row in hand
void CardRow::disableRowCardInteraction()
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->disableInteraction();
	}
}

// TODO, SPLIT OFF methods for hand into seperate class, Card Row on the field is very different than card row in hand
void CardRow::enableRowCardInteraction()
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->enableInteraction();
	}
}

void CardRow::clear()
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		this->removeChild(*it);
	}

	this->rowCards.clear();
	this->setCardPositions(Config::insertDelay);
}

void CardRow::setMouseOverCallback(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->setMouseOverCallback(callback);
	}
}

void CardRow::setMouseClickCallback(std::function<void(Card*)> callback)
{
	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		card->setMouseClickCallback(callback);
	}
}

void CardRow::setCardPositions(float cardRepositionDelay, float indexDelay)
{
	int cardCount = this->rowCards.size();
	int index = 0;

	float cardWidth = 225.0f * this->cardScale;
	float spacing = cardWidth + Config::defaultCardSpacing;

	float start = (spacing * (cardCount - 1)) / 2.0f;
	float end = ((cardCount - 1) * spacing) - (spacing * (cardCount - 1)) / 2.0f;

	// Update the spacing to overlap if too large
	if (end - start > this->rowWidth)
	{
		spacing = cardCount == 1 ? 0.0f : ((this->rowWidth - cardWidth) / (cardCount - 1));
	}

	for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
	{
		Card* card = *it;
		float newX = (index * spacing) - (spacing * (cardCount - 1)) / 2.0f;

		card->position = Vec2(newX, 0.0f);

		if (cardRepositionDelay > 0.0f)
		{
			card->stopAllActions();
			card->runAction(Sequence::create(
					DelayTime::create(index * indexDelay),
					EaseSineInOut::create(MoveTo::create(cardRepositionDelay, card->position)),
					nullptr
			));
			card->runAction(Sequence::create(
					DelayTime::create(index * indexDelay),
					ScaleTo::create(cardRepositionDelay, this->cardScale),
					nullptr
			));
		}
		else
		{
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

// Given a card, figure out what the effect would be, useful for AI calculations
int CardRow::simulateCardEffect(Card* card) 
{
	int diff = 0;

	switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				diff += this->getRowAttack();
				break;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_INV: {
				Card::Operation operation = Card::toOperation(card->cardData->cardType, 0);
				for (auto it = this->rowCards.begin(); it != this->rowCards.end(); it++)
				{
					Card* rowCard = *it;
					int before = rowCard->getAttack();
					int after = rowCard->simulateOperation(operation);
					diff += (after - before);
				}
			}
			default:
				break;
		}

	return diff;
}

bool CardRow::isEmpty()
{
	return this->rowCards.size() <= 0;
}

bool CardRow::isPlayerRow()
{
	return this->belongsToPlayer;
}

bool CardRow::isEnemyRow()
{
	return !this->belongsToPlayer;
}