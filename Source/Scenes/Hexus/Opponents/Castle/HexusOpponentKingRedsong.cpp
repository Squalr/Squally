#include "HexusOpponentKingRedsong.h"

const std::string HexusOpponentKingRedsong::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG";
HexusOpponentKingRedsong* HexusOpponentKingRedsong::instance = nullptr;

HexusOpponentKingRedsong* HexusOpponentKingRedsong::getInstance()
{
	if (HexusOpponentKingRedsong::instance == nullptr)
	{
		HexusOpponentKingRedsong::instance = new HexusOpponentKingRedsong();
	}

	return HexusOpponentKingRedsong::instance;
}

HexusOpponentKingRedsong::HexusOpponentKingRedsong() : HexusOpponentData(
	EntityResources::Environment_Castle_Npcs_KingRedsong_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentKingRedsong::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.6f),
	HexusOpponentData::generateDeck(25, 0.6f,
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

HexusOpponentKingRedsong::~HexusOpponentKingRedsong()
{
}
