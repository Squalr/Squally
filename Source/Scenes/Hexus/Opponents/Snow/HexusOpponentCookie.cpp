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
	EntityResources::Npcs_Cookie_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCookie::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.635f),
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
