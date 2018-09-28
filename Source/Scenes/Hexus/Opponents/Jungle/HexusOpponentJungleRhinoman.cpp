#include "HexusOpponentJungleRhinoman.h"

const std::string HexusOpponentJungleRhinoman::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Rhinoman";
HexusOpponentJungleRhinoman* HexusOpponentJungleRhinoman::instance = nullptr;

HexusOpponentJungleRhinoman* HexusOpponentJungleRhinoman::getInstance()
{
	if (HexusOpponentJungleRhinoman::instance == nullptr)
	{
		HexusOpponentJungleRhinoman::instance = new HexusOpponentJungleRhinoman();
	}

	return HexusOpponentJungleRhinoman::instance;
}

HexusOpponentJungleRhinoman::HexusOpponentJungleRhinoman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_BossRhinoman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentJungleRhinoman::StringKeyOpponentName,
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

HexusOpponentJungleRhinoman::~HexusOpponentJungleRhinoman()
{
}
