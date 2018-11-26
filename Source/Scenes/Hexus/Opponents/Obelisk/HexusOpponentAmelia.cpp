#include "HexusOpponentAmelia.h"

const std::string HexusOpponentAmelia::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AMELIA";
HexusOpponentAmelia* HexusOpponentAmelia::instance = nullptr;

HexusOpponentAmelia* HexusOpponentAmelia::getInstance()
{
	if (HexusOpponentAmelia::instance == nullptr)
	{
		HexusOpponentAmelia::instance = new HexusOpponentAmelia();
	}

	return HexusOpponentAmelia::instance;
}

HexusOpponentAmelia::HexusOpponentAmelia() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Npcs_Amelia_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAmelia::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.8f),
	HexusOpponentData::generateDeck(25, 0.8f,
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

HexusOpponentAmelia::~HexusOpponentAmelia()
{
}
