#include "HexusOpponentAphrodite.h"

const std::string HexusOpponentAphrodite::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APHRODITE";
HexusOpponentAphrodite* HexusOpponentAphrodite::instance = nullptr;

HexusOpponentAphrodite* HexusOpponentAphrodite::getInstance()
{
	if (HexusOpponentAphrodite::instance == nullptr)
	{
		HexusOpponentAphrodite::instance = new HexusOpponentAphrodite();
	}

	return HexusOpponentAphrodite::instance;
}

HexusOpponentAphrodite::HexusOpponentAphrodite() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Aphrodite_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAphrodite::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.4f,
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

HexusOpponentAphrodite::~HexusOpponentAphrodite()
{
}
