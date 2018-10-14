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
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Light,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary2),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
		{
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentTutorialF::~HexusOpponentTutorialF()
{
}
