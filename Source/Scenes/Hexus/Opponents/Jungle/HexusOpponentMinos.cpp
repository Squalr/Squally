#include "HexusOpponentMinos.h"

const std::string HexusOpponentMinos::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOS";
HexusOpponentMinos* HexusOpponentMinos::instance = nullptr;

HexusOpponentMinos* HexusOpponentMinos::getInstance()
{
	if (HexusOpponentMinos::instance == nullptr)
	{
		HexusOpponentMinos::instance = new HexusOpponentMinos();
	}

	return HexusOpponentMinos::instance;
}

HexusOpponentMinos::HexusOpponentMinos() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Minos_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentMinos::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
	},
	HexusOpponentData::generateDeck(25, 0.165f,
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

HexusOpponentMinos::~HexusOpponentMinos()
{
}
