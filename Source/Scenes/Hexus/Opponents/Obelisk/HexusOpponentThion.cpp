#include "HexusOpponentThion.h"

const std::string HexusOpponentThion::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THION";
HexusOpponentThion* HexusOpponentThion::instance = nullptr;

HexusOpponentThion* HexusOpponentThion::getInstance()
{
	if (HexusOpponentThion::instance == nullptr)
	{
		HexusOpponentThion::instance = new HexusOpponentThion();
	}

	return HexusOpponentThion::instance;
}

HexusOpponentThion::HexusOpponentThion() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Thion_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentThion::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.86f,
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

HexusOpponentThion::~HexusOpponentThion()
{
}
