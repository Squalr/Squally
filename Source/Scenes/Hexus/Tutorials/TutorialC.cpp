#include "TutorialC.h"

TutorialC* TutorialC::create()
{
	TutorialC* instance = new TutorialC();

	instance->autorelease();

	return instance;
}

TutorialC::TutorialC() : StateOverride(
	// Player losses
	0,
	// Enemy losses
	1,
	// Player's turn
	true,
	// Player passed
	false,
	// Enemy passed
	true,
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
		CardList::getInstance()->cardListByName->at(CardKeys::Binary14),
	},
	// Enemy hand
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal8),
	},
	// Player binary cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
	},
	// Player decimal cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
	},
	// Player hex cards
	std::vector<CardData*>
	{
	},
	// Enemy binary cards
	std::vector<CardData*>
	{
	},
	// Enemy decimal cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal13),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	})
{
}

TutorialC::~TutorialC()
{
}
