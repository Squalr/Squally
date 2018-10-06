#include "HexusOpponentRuinsTigerMan.h"

const std::string HexusOpponentRuinsTigerMan::StringKeyOpponentName = "Squally_Npc_Names_Ruins_TigerMan";
HexusOpponentRuinsTigerMan* HexusOpponentRuinsTigerMan::instance = nullptr;

HexusOpponentRuinsTigerMan* HexusOpponentRuinsTigerMan::getInstance()
{
	if (HexusOpponentRuinsTigerMan::instance == nullptr)
	{
		HexusOpponentRuinsTigerMan::instance = new HexusOpponentRuinsTigerMan();
	}

	return HexusOpponentRuinsTigerMan::instance;
}

HexusOpponentRuinsTigerMan::HexusOpponentRuinsTigerMan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_TigerMan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-16.0f, -72.0f),
	HexusOpponentRuinsTigerMan::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentRuinsTigerMan::~HexusOpponentRuinsTigerMan()
{
}
