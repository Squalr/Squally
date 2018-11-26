#include "HexusOpponentMarcel.h"

const std::string HexusOpponentMarcel::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MARCEL";
HexusOpponentMarcel* HexusOpponentMarcel::instance = nullptr;

HexusOpponentMarcel* HexusOpponentMarcel::getInstance()
{
	if (HexusOpponentMarcel::instance == nullptr)
	{
		HexusOpponentMarcel::instance = new HexusOpponentMarcel();
	}

	return HexusOpponentMarcel::instance;
}

HexusOpponentMarcel::HexusOpponentMarcel() : HexusOpponentData(
	EntityResources::Platformer_Environment_Mech_Npcs_Marcel_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentMarcel::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.92f),
	HexusOpponentData::generateDeck(25, 0.92f,
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

HexusOpponentMarcel::~HexusOpponentMarcel()
{
}
