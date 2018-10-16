#include "HexusOpponentKingGrogg.h"

const std::string HexusOpponentKingGrogg::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_GROGG";
HexusOpponentKingGrogg* HexusOpponentKingGrogg::instance = nullptr;

HexusOpponentKingGrogg* HexusOpponentKingGrogg::getInstance()
{
	if (HexusOpponentKingGrogg::instance == nullptr)
	{
		HexusOpponentKingGrogg::instance = new HexusOpponentKingGrogg();
	}

	return HexusOpponentKingGrogg::instance;
}

HexusOpponentKingGrogg::HexusOpponentKingGrogg() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_KingGrogg_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -112.0f),
	HexusOpponentKingGrogg::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.42f,
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

HexusOpponentKingGrogg::~HexusOpponentKingGrogg()
{
}
