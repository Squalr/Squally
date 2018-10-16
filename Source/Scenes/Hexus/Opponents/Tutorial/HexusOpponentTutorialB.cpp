#include "HexusOpponentTutorialB.h"

const std::string HexusOpponentTutorialB::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_B";
HexusOpponentTutorialB* HexusOpponentTutorialB::instance = nullptr;

HexusOpponentTutorialB* HexusOpponentTutorialB::getInstance()
{
	if (HexusOpponentTutorialB::instance == nullptr)
	{
		HexusOpponentTutorialB::instance = new HexusOpponentTutorialB();
	}

	return HexusOpponentTutorialB::instance;
}

HexusOpponentTutorialB::HexusOpponentTutorialB() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_PrincessNebea_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialB::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Air,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
	},
	HexusOpponentData::generateDeck(25, 0.07f,
		{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentTutorialB::~HexusOpponentTutorialB()
{
}
