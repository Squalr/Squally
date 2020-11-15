#include "CardRow.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

CardRow* CardRow::create(bool isPlayerRow)
{
    CardRow* instance = new (std::nothrow) CardRow(isPlayerRow);

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
	this->clearOperationsOnInsert = false;
	this->rowWidth = HexusConfig::rowWidth;

	this->rowSelectSprite = ClickableNode::create(HexusResources::RowSelection, HexusResources::RowSelectionHighlight);

	this->addChild(this->rowSelectSprite);
}

CardRow::~CardRow()
{
}

void CardRow::onEnter()
{
	super::onEnter();

	this->rowSelectSprite->setOpacity(0);
	this->rowSelectSprite->setVisible(false);
	this->setCardScale(Card::cardScale, 0.0f);
}

void CardRow::initializeListeners()
{
	super::initializeListeners();

	this->rowSelectSprite->setMouseClickCallback(CC_CALLBACK_0(CardRow::onRowSelectClick, this));
}

void CardRow::setRowWidth(float newRowWidth, float duration)
{
	this->rowWidth = newRowWidth;
	this->setCardPositions(duration);
}

void CardRow::setCardScale(float scale, float scaleSpeed)
{
	this->cardScale = scale;

	for (auto card : this->rowCards)
	{
		if (scaleSpeed > 0.0f)
		{
			card->stopAllActions();
			card->runAction(ScaleTo::create(scaleSpeed, this->cardScale));
		}
		else
		{
			card->setPosition(card->position);
			card->setScale(this->cardScale);
		}
	}
}

float CardRow::getCardScale()
{
	return this->cardScale;
}

void CardRow::insertCards(std::vector<Card*> cards, float cardInsertDelay, float indexDelay, bool asReentry)
{
	for (auto card : cards)
	{
		if (card == nullptr)
		{
			continue;
		}

		GameUtils::changeParent(card, this, true, asReentry);

		card->setMouseOverCallback(nullptr);
		card->setMouseClickCallback(nullptr);
		card->reveal();

		this->rowCards.push_back(card);

		if (this->clearOperationsOnInsert)
		{
			card->clearOperations();
		}
	}

	this->setCardPositions(cardInsertDelay, indexDelay);
}

void CardRow::insertCard(Card* card, float cardInsertDelay, bool asReentry)
{
	if (card == nullptr)
	{
		return;
	}

	GameUtils::changeParent(card, this, true, asReentry);

	card->setMouseOverCallback(nullptr);
	card->setMouseClickCallback(nullptr);
	card->reveal();

	this->rowCards.push_back(card);
	this->setCardPositions(cardInsertDelay);

	if (this->clearOperationsOnInsert)
	{
		card->clearOperations();
	}
}

void CardRow::insertCardsFront(std::vector<Card*> cards, float cardInsertDelay, float indexDelay, bool asReentry)
{
	for (auto card : cards)
	{
		if (card == nullptr)
		{
			continue;
		}

		GameUtils::changeParent(card, this, true, asReentry);

		card->setMouseOverCallback(nullptr);
		card->setMouseClickCallback(nullptr);
		card->reveal();

		this->rowCards.insert(this->rowCards.begin(), card);

		if (this->clearOperationsOnInsert)
		{
			card->clearOperations();
		}
	}

	this->setCardPositions(cardInsertDelay, indexDelay);
}

void CardRow::insertCardFront(Card* card, float cardInsertDelay, bool asReentry)
{
	if (card == nullptr)
	{
		return;
	}

	GameUtils::changeParent(card, this, true, asReentry);

	card->setMouseOverCallback(nullptr);
	card->setMouseClickCallback(nullptr);
	card->reveal();

	this->rowCards.insert(this->rowCards.begin(), card);
	this->setCardPositions(cardInsertDelay);

	if (this->clearOperationsOnInsert)
	{
		card->clearOperations();
	}
}

void CardRow::enableClearOperationsOnInsert()
{
	this->clearOperationsOnInsert = true;
}

Card* CardRow::removeCard(Card* card)
{
	if (std::find(this->rowCards.begin(), this->rowCards.end(), card) == this->rowCards.end())
	{
		// Not found
		return nullptr;
	}

	this->rowCards.erase(std::remove(this->rowCards.begin(), this->rowCards.end(), card), this->rowCards.end());
	this->setCardPositions(HexusConfig::insertDelay);

	return card; // Note: We let the caller remove the child because it allows for control over positioning
}

void CardRow::removeCardsWhere(std::function<bool(Card*)> predicate)
{
	// Note: If the caller wants the card list, they need to extract it in the predicate
	// Note: We let the caller remove the child because it allows for control over positioning
	auto removed = std::remove_if(this->rowCards.begin(), this->rowCards.end(), predicate);
	this->rowCards.erase(removed, this->rowCards.end());
	this->setCardPositions(HexusConfig::insertDelay);
}

int CardRow::getCardCount()
{
	return this->rowCards.size();
}

int CardRow::getRowAttack()
{
	int attack = 0;

	for (auto card : this->rowCards)
	{
		attack += card->getAttack();
	}

	return attack;
}

void CardRow::runEffect(CardEffects::CardEffect effect, std::vector<Card*> ignoreList)
{
	for (auto card : this->rowCards)
	{
		bool ignoreCard = false;

		for (auto ignoreIt = ignoreList.begin(); ignoreIt != ignoreList.end(); ignoreIt++)
		{
			if (*ignoreIt == card)
			{
				ignoreCard = true;
				break;
			}
		}

		if (!ignoreCard)
		{
			card->cardEffects->runEffect(effect);
		}
	}
}

void CardRow::clearEffects()
{
	for (auto card : this->rowCards)
	{
		card->cardEffects->clearEffects();
	}
}

void CardRow::enableRowSelection(std::function<void(CardRow*)> callback)
{
	this->rowSelectCallback = callback;

	this->rowSelectSprite->stopAllActions();

	this->rowSelectSprite->setVisible(true);
	this->rowSelectSprite->stopAllActions();

	this->rowSelectSprite->runAction(Sequence::create(FadeTo::create(0.25f, 255), nullptr));

	// Keep interaction so that mouseover is still possible, but set the callback to be the same as the row callback
	for (auto card : this->rowCards)
	{
		card->enableInteraction();
		card->setMouseClickCallback([=](Card* card) { callback(this); });
	}
}

void CardRow::enableRowCardSelection(std::function<void(Card*)> callback)
{
	for (auto card : this->rowCards)
	{
		card->setMouseClickCallback(callback);
		card->focus();
	}
}

void CardRow::disableRowSelection()
{
	this->rowSelectCallback = nullptr;

	ClickableNode* sprite = this->rowSelectSprite;

	this->rowSelectSprite->stopAllActions();
	this->rowSelectSprite->runAction(Sequence::create(
		FadeTo::create(0.25f, 0),
		CallFunc::create([sprite]
		{
			sprite->setVisible(false);
		}),
		nullptr
	));

	for (auto card : this->rowCards)
	{
		card->enableInteraction();
	}
}

void CardRow::disableRowCardSelection()
{
	for (auto card : this->rowCards)
	{
		card->setMouseClickCallback(nullptr);
		card->unfocus();
	}
}

void CardRow::disableRowCardInteraction()
{
	for (auto card : this->rowCards)
	{
		card->disableInteraction();
	}
}

void CardRow::enableRowCardInteraction()
{
	for (auto card : this->rowCards)
	{
		card->enableInteraction();
	}
}

void CardRow::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(this->rowCards.begin(), this->rowCards.end(), g);

	this->setCardPositions(0.0f);
}

void CardRow::clear()
{
	for (auto card : this->rowCards)
	{
		this->removeChild(card);
	}

	this->rowCards.clear();
	this->setCardPositions(HexusConfig::insertDelay);
}

void CardRow::setMouseOverCallback(std::function<void(Card*)> callback)
{
	for (auto card : this->rowCards)
	{
		card->setMouseOverCallback(callback);
	}
}

void CardRow::setMouseOutCallback(std::function<void(Card*)> callback)
{
	for (auto card : this->rowCards)
	{
		card->setMouseOutCallback(callback);
	}
}

void CardRow::setMouseClickCallback(std::function<void(Card*)> callback)
{
	for (auto card : this->rowCards)
	{
		card->setMouseClickCallback(callback);
	}
}

void CardRow::setCardPositions(float cardRepositionDelay, float indexDelay)
{
	const float cardWidth = 225.0f;

	int cardCount = this->rowCards.size();
	int index = 0;

	float scaledCardWidth = 225.0f * this->cardScale;
	float spacing = scaledCardWidth + HexusConfig::defaultCardSpacing;
	float length = spacing * cardCount;

	// Update the spacing to overlap if too large
	if (length > this->rowWidth)
	{
		spacing = cardCount == 0 ? 0.0f : (this->rowWidth / cardCount);
	}

	for (auto card : this->rowCards)
	{
		float newX = (index * spacing) - (spacing * (cardCount - 1)) / 2.0f;

		card->setLocalZOrder(index);
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
			card->stopAllActions();
			card->setPosition(card->position);
			card->setScale(this->cardScale);
		}

		index++;
	}
}

void CardRow::onRowSelectClick()
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

	switch (card->cardData->getCardType())
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
		case CardData::CardType::Special_ROL:
		case CardData::CardType::Special_ROR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_NOT:
		case CardData::CardType::Special_SUDDEN_DEATH:
		{
			for (auto rowCard : this->rowCards)
			{
				Card::Operation operation = card->toOperation(rowCard->cardData->getIntrinsicImmediate());
				int before = rowCard->getAttack();
				int after = rowCard->simulateOperation(operation);

				diff += (after - before);
			}
			
			break;
		}
		default:
		{
			break;
		}
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
