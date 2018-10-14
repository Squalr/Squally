#include "HexusOpponentThor.h"

const std::string HexusOpponentThor::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THOR";
HexusOpponentThor* HexusOpponentThor::instance = nullptr;

HexusOpponentThor* HexusOpponentThor::getInstance()
{
	if (HexusOpponentThor::instance == nullptr)
	{
		HexusOpponentThor::instance = new HexusOpponentThor();
	}

	return HexusOpponentThor::instance;
}

HexusOpponentThor::HexusOpponentThor() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Thor_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentThor::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
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

HexusOpponentThor::~HexusOpponentThor()
{
}
