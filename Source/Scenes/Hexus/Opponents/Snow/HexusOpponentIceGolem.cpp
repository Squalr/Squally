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
	Resources::Entities_Platformer_Environment_Snow_Enemies_IceGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-48.0f, -80.0f),
	HexusOpponentIceGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.75f,
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
