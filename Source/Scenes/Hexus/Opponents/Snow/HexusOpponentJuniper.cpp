#include "HexusOpponentJuniper.h"

const std::string HexusOpponentJuniper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JUNIPER";
HexusOpponentJuniper* HexusOpponentJuniper::instance = nullptr;

HexusOpponentJuniper* HexusOpponentJuniper::getInstance()
{
	if (HexusOpponentJuniper::instance == nullptr)
	{
		HexusOpponentJuniper::instance = new HexusOpponentJuniper();
	}

	return HexusOpponentJuniper::instance;
}

HexusOpponentJuniper::HexusOpponentJuniper() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Juniper_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentJuniper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.665f),
	HexusOpponentData::generateDeck(25, 0.665f,
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

HexusOpponentJuniper::~HexusOpponentJuniper()
{
}
