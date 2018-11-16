#include "TutorialB.h"

TutorialB* TutorialB::create()
{
	TutorialB* instance = new TutorialB();

	instance->autorelease();

	return instance;
}

TutorialB::TutorialB() : StateOverride(
	// Player losses
	1,
	// Enemy losses
	0,
	// Player's turn
	true,
	// Player passed
	false,
	// Enemy passed
	false,
	// Player deck
	std::vector<CardData*>
	{
	},
	// Enemy deck
	std::vector<CardData*>
	{
	},
	// Player hand
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal15),
	},
	// Enemy hand
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
	},
	// Player binary cards
	std::vector<CardData*>
	{
	},
	// Player decimal cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
	},
	// Player hex cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
	},
	// Enemy binary cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	// Enemy decimal cards
	std::vector<CardData*>
	{
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	})
{
}

TutorialB::~TutorialB()
{
}
