#include "HexusOpponentBodom.h"

const std::string HexusOpponentBodom::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BODOM";
HexusOpponentBodom* HexusOpponentBodom::instance = nullptr;

HexusOpponentBodom* HexusOpponentBodom::getInstance()
{
	if (HexusOpponentBodom::instance == nullptr)
	{
		HexusOpponentBodom::instance = new HexusOpponentBodom();
	}

	return HexusOpponentBodom::instance;
}

HexusOpponentBodom::HexusOpponentBodom() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Bodom_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentBodom::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
	},
	HexusOpponentData::generateDeck(25, 0, 4, 0.33f, 0.33f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentBodom::~HexusOpponentBodom()
{
}
