#include "TutorialA.h"

TutorialA* TutorialA::create()
{
	TutorialA* instance = new TutorialA();

	instance->autorelease();

	return instance;
}

TutorialA::TutorialA() : StateOverride(
	1,
	1,
	true,
	false,
	true,
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
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
	},
	std::vector<CardData*> { },
	std::vector<CardData*> { },
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
	},
	std::vector<CardData*> { },
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
	},
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
