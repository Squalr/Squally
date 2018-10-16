#include "HexusOpponentLycan.h"

const std::string HexusOpponentLycan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LYCAN";
HexusOpponentLycan* HexusOpponentLycan::instance = nullptr;

HexusOpponentLycan* HexusOpponentLycan::getInstance()
{
	if (HexusOpponentLycan::instance == nullptr)
	{
		HexusOpponentLycan::instance = new HexusOpponentLycan();
	}

	return HexusOpponentLycan::instance;
}

HexusOpponentLycan::HexusOpponentLycan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Lycan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentLycan::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.3f,
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

HexusOpponentLycan::~HexusOpponentLycan()
{
}
