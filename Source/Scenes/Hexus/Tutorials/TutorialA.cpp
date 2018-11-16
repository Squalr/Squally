#include "TutorialA.h"

TutorialA* TutorialA::create()
{
	TutorialA* instance = new TutorialA();

	instance->autorelease();

	return instance;
}

TutorialA::TutorialA() : StateOverride(
	// Player losses
	1,
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
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
	},
	// Enemy deck
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
	},
	// Player hand
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	},
	// Enemy hand
	std::vector<CardData*>
	{
	},
	// Player binary cards
	std::vector<CardData*>
	{
	},
	// Player decimal cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
	},
	// Player hex cards
	std::vector<CardData*>
	{
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
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
	})
{
}

TutorialA::~TutorialA()
{
}
