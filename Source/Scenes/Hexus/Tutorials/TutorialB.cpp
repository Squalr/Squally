#include "TutorialB.h"

TutorialB* TutorialB::create()
{
	TutorialB* instance = new TutorialB();

	instance->autorelease();

	return instance;
}

TutorialB::TutorialB() : StateOverride(
	1,
	0,
	true,
	false,
	false,
	std::vector<CardData*>
	{
	},
	std::vector<CardData*>
	{
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal15),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
	},
	std::vector<CardData*>
	{
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
	},
	std::vector<CardData*>
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	})
{
}

TutorialB::~TutorialB()
{
}
