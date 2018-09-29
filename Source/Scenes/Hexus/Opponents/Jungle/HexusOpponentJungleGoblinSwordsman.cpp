#include "HexusOpponentJungleGoblinSwordsman.h"

const std::string HexusOpponentJungleGoblinSwordsman::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Goblin_Swordsman";
HexusOpponentJungleGoblinSwordsman* HexusOpponentJungleGoblinSwordsman::instance = nullptr;

HexusOpponentJungleGoblinSwordsman* HexusOpponentJungleGoblinSwordsman::getInstance()
{
	if (HexusOpponentJungleGoblinSwordsman::instance == nullptr)
	{
		HexusOpponentJungleGoblinSwordsman::instance = new HexusOpponentJungleGoblinSwordsman();
	}

	return HexusOpponentJungleGoblinSwordsman::instance;
}

HexusOpponentJungleGoblinSwordsman::HexusOpponentJungleGoblinSwordsman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinSwordsman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.4f,
	Vec2(48.0f, -144.0f),
	Vec2(16.0f, -96.0f),
	HexusOpponentJungleGoblinSwordsman::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
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

HexusOpponentJungleGoblinSwordsman::~HexusOpponentJungleGoblinSwordsman()
{
}
