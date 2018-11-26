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
	EntityResources::Platformer_Environment_Jungle_Enemies_Barbarian_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentBarbarian::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.175f),
	HexusOpponentData::generateDeck(25, 0.175f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentBarbarian::~HexusOpponentBarbarian()
{
}
