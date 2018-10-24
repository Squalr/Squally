#include "HexusOpponentTutorialA.h"

const std::string HexusOpponentTutorialA::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_A";
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
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialA::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Light,
	HexusOpponentData::generateReward(0.07f),
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

HexusOpponentTutorialA::~HexusOpponentTutorialA()
{
}
