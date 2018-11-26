#include "HexusOpponentPrincessNebea.h"

const std::string HexusOpponentPrincessNebea::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_NEBEA";
HexusOpponentPrincessNebea* HexusOpponentPrincessNebea::instance = nullptr;

HexusOpponentPrincessNebea* HexusOpponentPrincessNebea::getInstance()
{
	if (HexusOpponentPrincessNebea::instance == nullptr)
	{
		HexusOpponentPrincessNebea::instance = new HexusOpponentPrincessNebea();
	}

	return HexusOpponentPrincessNebea::instance;
}

HexusOpponentPrincessNebea::HexusOpponentPrincessNebea() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Npcs_PrincessNebea_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPrincessNebea::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.89f),
	HexusOpponentData::generateDeck(25, 0.89f,
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

HexusOpponentPrincessNebea::~HexusOpponentPrincessNebea()
{
}
