#include "TutorialE.h"

TutorialE* TutorialE::create()
{
	TutorialE* instance = new TutorialE();

	instance->autorelease();

	return instance;
}

TutorialE::TutorialE() : StateOverride(
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
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
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
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
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
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex14),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex15),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex14),
	})
{
}

TutorialE::~TutorialE()
{
}
