#include "HexusOpponentOrcGrunt.h"

const std::string HexusOpponentOrcGrunt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_GRUNT";
HexusOpponentOrcGrunt* HexusOpponentOrcGrunt::instance = nullptr;

HexusOpponentOrcGrunt* HexusOpponentOrcGrunt::getInstance()
{
	if (HexusOpponentOrcGrunt::instance == nullptr)
	{
		HexusOpponentOrcGrunt::instance = new HexusOpponentOrcGrunt();
	}

	return HexusOpponentOrcGrunt::instance;
}

HexusOpponentOrcGrunt::HexusOpponentOrcGrunt() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_OrcGrunt_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentOrcGrunt::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.315f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentOrcGrunt::~HexusOpponentOrcGrunt()
{
}
