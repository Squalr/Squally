#include "HexusOpponentPrincessMatu.h"

const std::string HexusOpponentPrincessMatu::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MATU";
HexusOpponentPrincessMatu* HexusOpponentPrincessMatu::instance = nullptr;

HexusOpponentPrincessMatu* HexusOpponentPrincessMatu::getInstance()
{
	if (HexusOpponentPrincessMatu::instance == nullptr)
	{
		HexusOpponentPrincessMatu::instance = new HexusOpponentPrincessMatu();
	}

	return HexusOpponentPrincessMatu::instance;
}

HexusOpponentPrincessMatu::HexusOpponentPrincessMatu() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_PrincessMatu_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentPrincessMatu::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
	},
	HexusOpponentData::generateDeck(25, 0.15f,
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

HexusOpponentPrincessMatu::~HexusOpponentPrincessMatu()
{
}
