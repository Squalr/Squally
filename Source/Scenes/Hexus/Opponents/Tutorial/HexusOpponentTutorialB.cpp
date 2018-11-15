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
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Air,
	HexusOpponentData::generateReward(0.075f),
	HexusOpponentData::generateDeck(25, 0.075f,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	}),
	TutorialB::create()
	)
{
}

HexusOpponentTutorialB::~HexusOpponentTutorialB()
{
}
