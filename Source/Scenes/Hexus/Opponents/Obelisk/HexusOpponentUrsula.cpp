#include "HexusOpponentUrsula.h"

const std::string HexusOpponentUrsula::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_URSULA";
HexusOpponentUrsula* HexusOpponentUrsula::instance = nullptr;

HexusOpponentUrsula* HexusOpponentUrsula::getInstance()
{
	if (HexusOpponentUrsula::instance == nullptr)
	{
		HexusOpponentUrsula::instance = new HexusOpponentUrsula();
	}

	return HexusOpponentUrsula::instance;
}

HexusOpponentUrsula::HexusOpponentUrsula() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Npcs_Ursula_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentUrsula::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.87f),
	HexusOpponentData::generateDeck(25, 0.87f,
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

HexusOpponentUrsula::~HexusOpponentUrsula()
{
}
