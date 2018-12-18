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
	EntityResources::Npcs_CastleValgrind_Raven_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-24.0f, -32.0f),
	HexusOpponentRaven::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.59f),
	HexusOpponentData::generateDeck(25, 0.59f,
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
