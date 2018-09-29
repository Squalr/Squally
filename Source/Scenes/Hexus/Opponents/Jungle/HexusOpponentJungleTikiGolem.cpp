#include "HexusOpponentJungleTikiGolem.h"

const std::string HexusOpponentJungleTikiGolem::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Tiki_Golem";
HexusOpponentJungleTikiGolem* HexusOpponentJungleTikiGolem::instance = nullptr;

HexusOpponentJungleTikiGolem* HexusOpponentJungleTikiGolem::getInstance()
{
	if (HexusOpponentJungleTikiGolem::instance == nullptr)
	{
		HexusOpponentJungleTikiGolem::instance = new HexusOpponentJungleTikiGolem();
	}

	return HexusOpponentJungleTikiGolem::instance;
}

HexusOpponentJungleTikiGolem::HexusOpponentJungleTikiGolem() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_TikiGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -144.0f),
	Vec2(-16.0f, -112.0f),
	HexusOpponentJungleTikiGolem::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleTikiGolem::~HexusOpponentJungleTikiGolem()
{
}
