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
	EntityResources::Npcs_Thion_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentThion::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.86f),
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
