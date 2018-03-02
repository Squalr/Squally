#include "Deck.h"

Deck* Deck::create()
{
	Deck* deck = new Deck();

	deck->autorelease();

	return deck;
}

Deck* Deck::create(Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	Deck* deck = new Deck(cardStyle, cards);

	deck->autorelease();

	return deck;
}

Deck::Deck()
{
	this->deckCards = new std::vector<Card*>();
}

Deck::Deck(Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	this->style = cardStyle;
	this->deckCards = new std::vector<Card*>();

	for (auto it = cards->begin(); it != cards->end(); *it++)
	{
		this->insertCardBottom(Card::create(this->style, *it));
	}
}

Deck::~Deck()
{
	delete(this->deckCards);
}

void Deck::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void Deck::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Deck::initializeListeners()
{
}

void Deck::copyTo(Deck* otherDeck)
{
	otherDeck->clear();
	otherDeck->style = this->style;

	for (auto it = this->deckCards->begin(); it != this->deckCards->end(); *it++)
	{
		otherDeck->insertCardRandom(Card::create(this->style, (*it)->cardData));
	}
}

int Deck::getCardCount()
{
	return this->deckCards->size();
}

Card* Deck::drawCard()
{
	Card* card = this->deckCards->back();

	this->deckCards->pop_back();

	// Note: We let the caller remove the child because it allows for control over positioning

	return card;
}

bool Deck::hasCards()
{
	if (this->deckCards->size() > 0)
	{
		return true;
	}

	return false;
}

void Deck::insertCardTop(Card* card)
{
	card->hide();
	this->deckCards->push_back(card);
	GameUtils::changeParent(card, this, false);
}

void Deck::insertCardBottom(Card* card)
{
	card->hide();
	this->deckCards->insert(this->deckCards->begin(), card);
	GameUtils::changeParent(card, this, false);
}

void Deck::insertCardRandom(Card* card)
{
	int index = RandomHelper::random_int(0, (int)this->deckCards->size());

	card->hide();
	this->deckCards->insert(this->deckCards->begin() + index, card);
	GameUtils::changeParent(card, this, false);
}

void Deck::clear()
{
	this->removeAllChildren();
	this->deckCards->clear();
}

void Deck::setCardOrder()
{
	// Fix the order of all cards in the deck
	for (auto it = this->deckCards->begin(); it != this->deckCards->end(); it++)
	{
		Card* card = *it;
		card->retain();
		this->removeChild(card);
		this->addChild(card);
	}
}