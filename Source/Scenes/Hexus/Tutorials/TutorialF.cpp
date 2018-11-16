#include "TutorialF.h"

TutorialF* TutorialF::create()
{
	TutorialF* instance = new TutorialF();

	instance->autorelease();

	return instance;
}

TutorialF::TutorialF() : StateOverride(
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
		CardList::getInstance()->cardListByName->at(CardKeys::Mov),
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
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
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
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal15),
	},
	// Enemy hex cards
	std::vector<CardData*>
	{
	})
{
}

TutorialF::~TutorialF()
{
}
