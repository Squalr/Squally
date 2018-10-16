#include "HexusOpponentCookie.h"

const std::string HexusOpponentCookie::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_COOKIE";
HexusOpponentCookie* HexusOpponentCookie::instance = nullptr;

HexusOpponentCookie* HexusOpponentCookie::getInstance()
{
	if (HexusOpponentCookie::instance == nullptr)
	{
		HexusOpponentCookie::instance = new HexusOpponentCookie();
	}

	return HexusOpponentCookie::instance;
}

HexusOpponentCookie::HexusOpponentCookie() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Cookie_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCookie::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.635f,
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

HexusOpponentCookie::~HexusOpponentCookie()
{
}
