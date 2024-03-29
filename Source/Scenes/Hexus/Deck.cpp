#include "Deck.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

Deck* Deck::create(bool isPlayerOwnedDeck)
{
	Deck* instance = new Deck(isPlayerOwnedDeck);

	instance->autorelease();

	return instance;
}

Deck* Deck::create(Card::CardStyle cardStyle, std::vector<CardData*> cards, bool isPlayerOwnedDeck)
{
	Deck* instance = new Deck(cardStyle, cards, isPlayerOwnedDeck);

	instance->autorelease();

	return instance;
}

Deck::Deck(bool isPlayerOwnedDeck) : Deck(Card::CardStyle::Earth, std::vector<CardData*>(), isPlayerOwnedDeck)
{
}

Deck::Deck(Card::CardStyle cardStyle, std::vector<CardData*> cardData, bool isPlayerOwnedDeck)
{
	this->isPlayerOwnedDeck = isPlayerOwnedDeck;
	this->style = cardStyle;
	this->pad = ClickableNode::create(HexusResources::CardPad, HexusResources::CardPad);
	this->cardsNode = Node::create();
	this->deckFocus = Sprite::create(HexusResources::CardSelect);

	this->pad->setScale(Card::cardScale);
	this->deckFocus->setScale(Card::cardScale);

	this->addChild(this->pad);

	for (CardData* next : cardData)
	{
		this->insertCardBottom(Card::create(this->style, next, isPlayerOwnedDeck), false, 0.0f);
	}

	this->addChild(this->cardsNode);
	this->addChild(this->deckFocus);
}

Deck::~Deck()
{
}

void Deck::copyTo(Deck* otherDeck)
{
	if (otherDeck != nullptr)
	{
		otherDeck->clear();
		otherDeck->style = this->style;

		for (auto next : this->deckCards)
		{
			otherDeck->insertCardRandom(Card::create(this->style, next->cardData, this->isPlayerOwnedDeck), false, 0.0f);
		}
	}
}

int Deck::getCardCount()
{
	return this->deckCards.size();
}

Card* Deck::drawCard()
{
	if (this->deckCards.size() <= 0)
	{
		return nullptr;
	}

	Card* card = this->deckCards.back();
	this->deckCards.pop_back();

	// Note: We let the caller remove the child because it allows for control over positioning
	return card;
}

void Deck::setCardScale(float scale, float scaleSpeed)
{
	for (auto card : this->deckCards)
	{
		if (scaleSpeed > 0.0f)
		{
			card->stopAllActions();
			card->runAction(ScaleTo::create(scaleSpeed, scale));
		}
		else
		{
			card->setPosition(card->position);
			card->setScale(scale);
		}
	}
}

bool Deck::hasCards()
{
	return this->deckCards.size() > 0;
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(this->deckCards.begin(), this->deckCards.end(), g);
	this->setCardOrder();
}

void Deck::insertCardTop(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this->cardsNode, true);

	this->deckCards.push_back(card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);

	if (this->clearOperationsOnInsert)
	{
		card->clearOperations();
	}
}

void Deck::insertCardBottom(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this->cardsNode, true);

	this->deckCards.insert(this->deckCards.begin(), card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);

	if (this->clearOperationsOnInsert)
	{
		card->clearOperations();
	}
}

void Deck::insertCardRandom(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this->cardsNode, true);

	int index = RandomHelper::random_int(0, (int)this->deckCards.size());
	this->deckCards.insert(this->deckCards.begin() + index, card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);

	if (this->clearOperationsOnInsert)
	{
		card->clearOperations();
	}
}

void Deck::enableClearOperationsOnInsert()
{
	this->clearOperationsOnInsert = true;
}

void Deck::doInsertAnimation(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	if (faceUp)
	{
		card->reveal();
	}
	else
	{
		card->hide();
	}

	card->setMouseOverCallback(nullptr);
	card->setMouseClickCallback(nullptr);
	card->stopAllActions();

	if (insertDelay <= 0.0f)
	{
		card->setScale(Card::cardScale);
		card->setPosition(Vec2::ZERO);
	}
	else
	{
		card->runAction(ScaleTo::create(insertDelay, Card::cardScale));
		card->runAction(MoveTo::create(insertDelay, Vec2::ZERO));
	}
}

void Deck::clear()
{
	for (auto card : this->deckCards)
	{
		this->cardsNode->removeChild(card);
	}

	this->deckCards.clear();
}

void Deck::setCardOrder()
{
	int zIndex = 0;

	// Pad is always first
	this->pad->setLocalZOrder(zIndex++);

	// Fix the Z order of all cards.
	// Note: Normally we prefer to keep nodes added in the correct order, but removing/re-adding nodes here can inturrupt animations.
	for (auto next : this->deckCards)
	{
		next->setLocalZOrder(zIndex++);
	}
}

void Deck::enableDeckSelection(std::function<void(Deck*)> callback)
{
	this->pad->enableInteraction();
	this->pad->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		callback(this);
	});

	this->deckFocus->setOpacity(196);
}

void Deck::disableDeckSelection()
{
	this->pad->disableInteraction();
	this->pad->setMouseClickCallback(nullptr);

	this->deckFocus->setOpacity(0);
}

void Deck::removeCardsWhere(std::function<bool(Card*)> predicate)
{
	// Note: If the caller wants the card list, they need to extract it in the predicate
	// Note: We let the caller remove the child because it allows for control over positioning
	auto removed = std::remove_if(this->deckCards.begin(), this->deckCards.end(), predicate);
	this->deckCards.erase(removed, this->deckCards.end());
	this->setCardOrder();
}

Card* Deck::removeCard(Card* card)
{
	if (card == nullptr)
	{
		return nullptr;
	}

	this->deckCards.erase(std::remove(this->deckCards.begin(), this->deckCards.end(), card), this->deckCards.end());
	this->setCardOrder();

	// Note: We let the caller remove the child because it allows for control over positioning
	return card;
}

void Deck::enableTopCardInteraction(std::function<void(Card*)> mouseOverCallback)
{
	if (!this->deckCards.empty())
	{
		this->deckCards.back()->enableInteraction();
		this->deckCards.back()->setMouseOverCallback(mouseOverCallback);
	}
}

void Deck::disableInteraction()
{
	for (auto card : this->deckCards)
	{
		card->disableInteraction();
		card->setMouseOverCallback(nullptr);
	}
}

void Deck::setCardPositions(float cardRepositionDelay, float indexDelay)
{
	int index = 0;

	for (auto card : this->deckCards)
	{
		card->setLocalZOrder(index);
		card->position = Vec2::ZERO;

		if (cardRepositionDelay > 0.0f)
		{
			card->stopAllActions();
			card->runAction(Sequence::create(
					DelayTime::create(index * indexDelay),
					EaseSineInOut::create(MoveTo::create(cardRepositionDelay, card->position)),
					nullptr
			));
		}
		else
		{
			card->stopAllActions();
			card->setPosition(card->position);
		}

		index++;
	}
}
