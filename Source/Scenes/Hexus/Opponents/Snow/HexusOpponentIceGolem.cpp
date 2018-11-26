#include "HexusOpponentIceGolem.h"

const std::string HexusOpponentIceGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ICE_GOLEM";
HexusOpponentIceGolem* HexusOpponentIceGolem::instance = nullptr;

HexusOpponentIceGolem* HexusOpponentIceGolem::getInstance()
{
	if (HexusOpponentIceGolem::instance == nullptr)
	{
		HexusOpponentIceGolem::instance = new HexusOpponentIceGolem();
	}

	return HexusOpponentIceGolem::instance;
}

HexusOpponentIceGolem::HexusOpponentIceGolem() : HexusOpponentData(
	EntityResources::Platformer_Environment_Snow_Enemies_IceGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-48.0f, -80.0f),
	HexusOpponentIceGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.66f),
	HexusOpponentData::generateDeck(25, 0.66f,
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

HexusOpponentIceGolem::~HexusOpponentIceGolem()
{
}
