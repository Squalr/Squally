#include "HexusOpponentRoger.h"

const std::string HexusOpponentRoger::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROGER";
HexusOpponentRoger* HexusOpponentRoger::instance = nullptr;

HexusOpponentRoger* HexusOpponentRoger::getInstance()
{
	if (HexusOpponentRoger::instance == nullptr)
	{
		HexusOpponentRoger::instance = new HexusOpponentRoger();
	}

	return HexusOpponentRoger::instance;
}

HexusOpponentRoger::HexusOpponentRoger() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Roger_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentRoger::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 12, 0.33f, 0.33f,
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

HexusOpponentRoger::~HexusOpponentRoger()
{
}
