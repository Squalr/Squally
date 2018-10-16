#include "HexusOpponentLionMan.h"

const std::string HexusOpponentLionMan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LION_MAN";
HexusOpponentLionMan* HexusOpponentLionMan::instance = nullptr;

HexusOpponentLionMan* HexusOpponentLionMan::getInstance()
{
	if (HexusOpponentLionMan::instance == nullptr)
	{
		HexusOpponentLionMan::instance = new HexusOpponentLionMan();
	}

	return HexusOpponentLionMan::instance;
}

HexusOpponentLionMan::HexusOpponentLionMan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_LionMan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-24.0f, -24.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentLionMan::OpponentSaveKey,
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

HexusOpponentLionMan::~HexusOpponentLionMan()
{
}
