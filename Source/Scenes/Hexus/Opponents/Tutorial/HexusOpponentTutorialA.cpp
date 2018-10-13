#include "HexusOpponentTutorialA.h"

const std::string HexusOpponentTutorialA::StringKeyOpponentName = "Squally_Npc_Names_Tutorial_A";
HexusOpponentTutorialA* HexusOpponentTutorialA::instance = nullptr;

HexusOpponentTutorialA* HexusOpponentTutorialA::getInstance()
{
	if (HexusOpponentTutorialA::instance == nullptr)
	{
		HexusOpponentTutorialA::instance = new HexusOpponentTutorialA();
	}

	return HexusOpponentTutorialA::instance;
}

HexusOpponentTutorialA::HexusOpponentTutorialA() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_KingRedsong_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialA::StringKeyOpponentName,
	GameState::Difficulty::Stupid,
	Card::CardStyle::Light,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary2),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
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
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentTutorialA::~HexusOpponentTutorialA()
{
}
