#include "HexusOpponentJungleJungleDragon.h"

const std::string HexusOpponentJungleJungleDragon::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Jungle_Dragon";
HexusOpponentJungleJungleDragon* HexusOpponentJungleJungleDragon::instance = nullptr;

HexusOpponentJungleJungleDragon* HexusOpponentJungleJungleDragon::getInstance()
{
	if (HexusOpponentJungleJungleDragon::instance == nullptr)
	{
		HexusOpponentJungleJungleDragon::instance = new HexusOpponentJungleJungleDragon();
	}

	return HexusOpponentJungleJungleDragon::instance;
}

HexusOpponentJungleJungleDragon::HexusOpponentJungleJungleDragon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_JungleDragon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentJungleJungleDragon::StringKeyOpponentName,
	Card::CardStyle::Earth,
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

HexusOpponentJungleJungleDragon::~HexusOpponentJungleJungleDragon()
{
}
