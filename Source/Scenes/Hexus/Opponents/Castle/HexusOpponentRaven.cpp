#include "HexusOpponentRaven.h"

const std::string HexusOpponentRaven::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAVEN";
HexusOpponentRaven* HexusOpponentRaven::instance = nullptr;

HexusOpponentRaven* HexusOpponentRaven::getInstance()
{
	if (HexusOpponentRaven::instance == nullptr)
	{
		HexusOpponentRaven::instance = new HexusOpponentRaven();
	}

	return HexusOpponentRaven::instance;
}

HexusOpponentRaven::HexusOpponentRaven() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Raven_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-24.0f, -32.0f),
	HexusOpponentRaven::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0, 9, 0.33f, 0.33f,
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

HexusOpponentRaven::~HexusOpponentRaven()
{
}
