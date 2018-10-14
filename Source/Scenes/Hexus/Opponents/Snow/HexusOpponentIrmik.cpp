#include "HexusOpponentIrmik.h"

const std::string HexusOpponentIrmik::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_IRMIK";
HexusOpponentIrmik* HexusOpponentIrmik::instance = nullptr;

HexusOpponentIrmik* HexusOpponentIrmik::getInstance()
{
	if (HexusOpponentIrmik::instance == nullptr)
	{
		HexusOpponentIrmik::instance = new HexusOpponentIrmik();
	}

	return HexusOpponentIrmik::instance;
}

HexusOpponentIrmik::HexusOpponentIrmik() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Irmik_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentIrmik::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 10, 0.33f, 0.33f,
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

HexusOpponentIrmik::~HexusOpponentIrmik()
{
}
