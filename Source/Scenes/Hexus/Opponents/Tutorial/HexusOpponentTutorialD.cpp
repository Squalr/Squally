#include "HexusOpponentTutorialD.h"

const std::string HexusOpponentTutorialD::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_D";
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
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Zana_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentTutorialD::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.09f),
	HexusOpponentData::generateDeck(25, 0.09f,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})//,
	//TutorialD::create()
	)
{
}

HexusOpponentTutorialD::~HexusOpponentTutorialD()
{
}
