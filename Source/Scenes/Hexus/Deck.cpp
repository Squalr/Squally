#include "Deck.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

Deck* Deck::create()
{
	Deck* instance = new Deck();

	instance->autorelease();

	return instance;
}

Deck* Deck::create(Card::CardStyle cardStyle, std::vector<CardData*> cards)
{
	Deck* instance = new Deck(cardStyle, cards);

	instance->autorelease();

	return instance;
}

Deck::Deck() : Deck(Card::CardStyle::Earth, std::vector<CardData*>())
{
	this->deckCards = std::vector<Card*>();
}

Deck::Deck(Card::CardStyle cardStyle, std::vector<CardData*> cardData)
{
	this->style = cardStyle;
	this->deckCards = std::vector<Card*>();
	this->pad = Sprite::create(HexusResources::CardPad);

	this->pad->setScale(Card::cardScale);

	this->addChild(this->pad);

	for (auto it = cardData.begin(); it != cardData.end(); *it++)
	{
		this->insertCardBottom(Card::create(this->style, *it), false, 0.0f);
	}
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

		for (auto it = this->deckCards.begin(); it != this->deckCards.end(); *it++)
		{
			otherDeck->insertCardRandom(Card::create(this->style, (*it)->cardData), false, 0.0f);
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

bool Deck::hasCards()
{
	return this->deckCards.size() > 0;
}

void Deck::shuffle()
{
	std::random_shuffle(this->deckCards.begin(), this->deckCards.end());
	this->setCardOrder();
}

void Deck::insertCardTop(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this, true);

	this->deckCards.push_back(card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);
}

void Deck::insertCardBottom(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this, true);

	this->deckCards.insert(this->deckCards.begin(), card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);
}

void Deck::insertCardRandom(Card* card, bool faceUp, float insertDelay)
{
	if (card == nullptr)
	{
		return;
	}

	card->disableInteraction();

	GameUtils::changeParent(card, this, true);

	int index = RandomHelper::random_int(0, (int)this->deckCards.size());
	this->deckCards.insert(this->deckCards.begin() + index, card);
	this->setCardOrder();
	this->doInsertAnimation(card, faceUp, insertDelay);
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
	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		this->removeChild(*it);
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
	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		(*it)->setLocalZOrder(zIndex++);
	}
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
