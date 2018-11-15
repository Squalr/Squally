#include "PuzzleA.h"

PuzzleA* PuzzleA::create()
{
	PuzzleA* instance = new PuzzleA();

	instance->autorelease();

	return instance;
}

PuzzleA::PuzzleA() : StateOverride(
	1,
	1,
	true,
	false,
	true,
	std::vector<CardData*> { },
	std::vector<CardData*> { },
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	},
	std::vector<CardData*> { },
	std::vector<CardData*> { },
	std::vector<CardData*> { },
	std::vector<CardData*> { },
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	})
{
}

PuzzleA::~PuzzleA()
{
}
