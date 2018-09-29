#include "HexusOpponentJungleMantis.h"

const std::string HexusOpponentJungleMantis::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Mantis";
HexusOpponentJungleMantis* HexusOpponentJungleMantis::instance = nullptr;

HexusOpponentJungleMantis* HexusOpponentJungleMantis::getInstance()
{
	if (HexusOpponentJungleMantis::instance == nullptr)
	{
		HexusOpponentJungleMantis::instance = new HexusOpponentJungleMantis();
	}

	return HexusOpponentJungleMantis::instance;
}

HexusOpponentJungleMantis::HexusOpponentJungleMantis() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Mantis_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.8f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentJungleMantis::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal8),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex8),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip1),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleMantis::~HexusOpponentJungleMantis()
{
}
