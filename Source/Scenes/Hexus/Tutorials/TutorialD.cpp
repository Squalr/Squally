#include "TutorialD.h"

TutorialD* TutorialD::create()
{
	TutorialD* instance = new TutorialD();

	instance->autorelease();

	return instance;
}

TutorialD::TutorialD() : StateOverride(
	// Player losses
	1,
	// Enemy losses
	1,
	// Player's turn
	true,
	// Player passed
	false,
	// Enemy passed
	false,
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
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	},
	// Enemy hand
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex8),
	},
	// Player binary cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
	},
	// Player decimal cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex14),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex10),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
	},
	// Player hex cards
	std::vector<CardData*>
	{
	},
	// Enemy binary cards
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary10),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary11),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary9),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary13),
	},
	// Enemy decimal cards
	std::vector<CardData*>
	{
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
	})
{
}

TutorialD::~TutorialD()
{
}
