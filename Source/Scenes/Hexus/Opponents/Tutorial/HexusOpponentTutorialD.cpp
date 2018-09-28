#include "HexusOpponentTutorialD.h"

const std::string HexusOpponentTutorialD::StringKeyOpponentName = "Squally_Npc_Names_Tutorial_D";
HexusOpponentTutorialD* HexusOpponentTutorialD::instance = nullptr;

HexusOpponentTutorialD* HexusOpponentTutorialD::getInstance()
{
	if (HexusOpponentTutorialD::instance == nullptr)
	{
		HexusOpponentTutorialD::instance = new HexusOpponentTutorialD();
	}

	return HexusOpponentTutorialD::instance;
}

HexusOpponentTutorialD::HexusOpponentTutorialD() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Knightess_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentTutorialD::StringKeyOpponentName, Card::CardStyle::Earth,
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

HexusOpponentTutorialD::~HexusOpponentTutorialD()
{
}
