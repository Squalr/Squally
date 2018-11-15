#include "HexusOpponentPrincessPepper.h"

const std::string HexusOpponentPrincessPepper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_PEPPER";
HexusOpponentPrincessPepper* HexusOpponentPrincessPepper::instance = nullptr;

HexusOpponentPrincessPepper* HexusOpponentPrincessPepper::getInstance()
{
	if (HexusOpponentPrincessPepper::instance == nullptr)
	{
		HexusOpponentPrincessPepper::instance = new HexusOpponentPrincessPepper();
	}

	return HexusOpponentPrincessPepper::instance;
}

HexusOpponentPrincessPepper::HexusOpponentPrincessPepper() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_PrincessPepper_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPrincessPepper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.7f),
	HexusOpponentData::generateDeck(25, 0.7f,
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

HexusOpponentPrincessPepper::~HexusOpponentPrincessPepper()
{
}
