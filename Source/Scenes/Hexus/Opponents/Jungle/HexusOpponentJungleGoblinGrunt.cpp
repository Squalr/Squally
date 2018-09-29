#include "HexusOpponentJungleGoblinGrunt.h"

const std::string HexusOpponentJungleGoblinGrunt::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Goblin_Grunt";
HexusOpponentJungleGoblinGrunt* HexusOpponentJungleGoblinGrunt::instance = nullptr;

HexusOpponentJungleGoblinGrunt* HexusOpponentJungleGoblinGrunt::getInstance()
{
	if (HexusOpponentJungleGoblinGrunt::instance == nullptr)
	{
		HexusOpponentJungleGoblinGrunt::instance = new HexusOpponentJungleGoblinGrunt();
	}

	return HexusOpponentJungleGoblinGrunt::instance;
}

HexusOpponentJungleGoblinGrunt::HexusOpponentJungleGoblinGrunt() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinGrunt_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.4f,
	Vec2(48.0f, -144.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentJungleGoblinGrunt::StringKeyOpponentName,
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

HexusOpponentJungleGoblinGrunt::~HexusOpponentJungleGoblinGrunt()
{
}
