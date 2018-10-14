#include "HexusOpponentAppolo.h"

const std::string HexusOpponentAppolo::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APPOLO";
HexusOpponentAppolo* HexusOpponentAppolo::instance = nullptr;

HexusOpponentAppolo* HexusOpponentAppolo::getInstance()
{
	if (HexusOpponentAppolo::instance == nullptr)
	{
		HexusOpponentAppolo::instance = new HexusOpponentAppolo();
	}

	return HexusOpponentAppolo::instance;
}

HexusOpponentAppolo::HexusOpponentAppolo() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Appolo_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAppolo::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 7, 0.33f, 0.33f,
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

HexusOpponentAppolo::~HexusOpponentAppolo()
{
}
