#include "HexusOpponentDudly.h"

const std::string HexusOpponentDudly::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DUDLY";
HexusOpponentDudly* HexusOpponentDudly::instance = nullptr;

HexusOpponentDudly* HexusOpponentDudly::getInstance()
{
	if (HexusOpponentDudly::instance == nullptr)
	{
		HexusOpponentDudly::instance = new HexusOpponentDudly();
	}

	return HexusOpponentDudly::instance;
}

HexusOpponentDudly::HexusOpponentDudly() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Dudly_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-32.0f, -72.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentDudly::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.32f,
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

HexusOpponentDudly::~HexusOpponentDudly()
{
}
