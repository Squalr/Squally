#include "HexusOpponentBarbarian.h"

const std::string HexusOpponentBarbarian::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BARBARIAN";
HexusOpponentBarbarian* HexusOpponentBarbarian::instance = nullptr;

HexusOpponentBarbarian* HexusOpponentBarbarian::getInstance()
{
	if (HexusOpponentBarbarian::instance == nullptr)
	{
		HexusOpponentBarbarian::instance = new HexusOpponentBarbarian();
	}

	return HexusOpponentBarbarian::instance;
}

HexusOpponentBarbarian::HexusOpponentBarbarian() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Barbarian_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentBarbarian::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
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

HexusOpponentBarbarian::~HexusOpponentBarbarian()
{
}
