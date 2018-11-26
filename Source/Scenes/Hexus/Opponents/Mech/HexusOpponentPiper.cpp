#include "HexusOpponentPiper.h"

const std::string HexusOpponentPiper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PIPER";
HexusOpponentPiper* HexusOpponentPiper::instance = nullptr;

HexusOpponentPiper* HexusOpponentPiper::getInstance()
{
	if (HexusOpponentPiper::instance == nullptr)
	{
		HexusOpponentPiper::instance = new HexusOpponentPiper();
	}

	return HexusOpponentPiper::instance;
}

HexusOpponentPiper::HexusOpponentPiper() : HexusOpponentData(
	EntityResources::Platformer_Environment_Mech_Npcs_Piper_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPiper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.91f),
	HexusOpponentData::generateDeck(25, 0.91f,
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

HexusOpponentPiper::~HexusOpponentPiper()
{
}
