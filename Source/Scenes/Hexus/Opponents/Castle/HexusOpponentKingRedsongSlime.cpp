#include "HexusOpponentKingRedsongSlime.h"

const std::string HexusOpponentKingRedsongSlime::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG_SLIME";
HexusOpponentKingRedsongSlime* HexusOpponentKingRedsongSlime::instance = nullptr;

HexusOpponentKingRedsongSlime* HexusOpponentKingRedsongSlime::getInstance()
{
	if (HexusOpponentKingRedsongSlime::instance == nullptr)
	{
		HexusOpponentKingRedsongSlime::instance = new HexusOpponentKingRedsongSlime();
	}

	return HexusOpponentKingRedsongSlime::instance;
}

HexusOpponentKingRedsongSlime::HexusOpponentKingRedsongSlime() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_KingRedsongSlime_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-48.0f, -96.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentKingRedsongSlime::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.53f),
	HexusOpponentData::generateDeck(25, 0.53f,
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

HexusOpponentKingRedsongSlime::~HexusOpponentKingRedsongSlime()
{
}
