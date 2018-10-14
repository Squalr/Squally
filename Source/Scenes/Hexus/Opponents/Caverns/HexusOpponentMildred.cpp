#include "HexusOpponentMildred.h"

const std::string HexusOpponentMildred::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MILDRED";
HexusOpponentMildred* HexusOpponentMildred::instance = nullptr;

HexusOpponentMildred* HexusOpponentMildred::getInstance()
{
	if (HexusOpponentMildred::instance == nullptr)
	{
		HexusOpponentMildred::instance = new HexusOpponentMildred();
	}

	return HexusOpponentMildred::instance;
}

HexusOpponentMildred::HexusOpponentMildred() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Mildred_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.8f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentMildred::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0, 8, 0.33f, 0.33f,
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

HexusOpponentMildred::~HexusOpponentMildred()
{
}
