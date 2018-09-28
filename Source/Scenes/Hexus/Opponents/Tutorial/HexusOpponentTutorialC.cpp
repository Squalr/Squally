#include "HexusOpponentTutorialC.h"

const std::string HexusOpponentTutorialC::StringKeyOpponentName = "Squally_Npc_Names_Tutorial_C";
HexusOpponentTutorialC* HexusOpponentTutorialC::instance = nullptr;

HexusOpponentTutorialC* HexusOpponentTutorialC::getInstance()
{
	if (HexusOpponentTutorialC::instance == nullptr)
	{
		HexusOpponentTutorialC::instance = new HexusOpponentTutorialC();
	}

	return HexusOpponentTutorialC::instance;
}

HexusOpponentTutorialC::HexusOpponentTutorialC() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Wizard_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentTutorialC::StringKeyOpponentName, Card::CardStyle::Earth,
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

HexusOpponentTutorialC::~HexusOpponentTutorialC()
{
}
