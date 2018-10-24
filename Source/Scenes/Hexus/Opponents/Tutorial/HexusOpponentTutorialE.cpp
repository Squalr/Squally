#include "HexusOpponentTutorialE.h"

const std::string HexusOpponentTutorialE::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_E";
HexusOpponentTutorialE* HexusOpponentTutorialE::instance = nullptr;

HexusOpponentTutorialE* HexusOpponentTutorialE::getInstance()
{
	if (HexusOpponentTutorialE::instance == nullptr)
	{
		HexusOpponentTutorialE::instance = new HexusOpponentTutorialE();
	}

	return HexusOpponentTutorialE::instance;
}

HexusOpponentTutorialE::HexusOpponentTutorialE() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Irmik_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentTutorialE::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Water,
	HexusOpponentData::generateReward(0.095f),
	HexusOpponentData::generateDeck(25, 0.095f,
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

HexusOpponentTutorialE::~HexusOpponentTutorialE()
{
}
