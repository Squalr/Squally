#include "HexusOpponentTutorialF.h"

const std::string HexusOpponentTutorialF::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_F";
HexusOpponentTutorialF* HexusOpponentTutorialF::instance = nullptr;

HexusOpponentTutorialF* HexusOpponentTutorialF::getInstance()
{
	if (HexusOpponentTutorialF::instance == nullptr)
	{
		HexusOpponentTutorialF::instance = new HexusOpponentTutorialF();
	}

	return HexusOpponentTutorialF::instance;
}

HexusOpponentTutorialF::HexusOpponentTutorialF() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Griffin_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentTutorialF::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Light,
	HexusOpponentData::generateReward(0.1f),
	HexusOpponentData::generateDeck(25, 0.1f,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	}),
	TutorialF::create()
	)
{
}

HexusOpponentTutorialF::~HexusOpponentTutorialF()
{
}
