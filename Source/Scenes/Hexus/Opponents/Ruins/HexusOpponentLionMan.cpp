#include "HexusOpponentLionMan.h"

const std::string HexusOpponentLionMan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LION_MAN";
HexusOpponentLionMan* HexusOpponentLionMan::instance = nullptr;

HexusOpponentLionMan* HexusOpponentLionMan::getInstance()
{
	if (HexusOpponentLionMan::instance == nullptr)
	{
		HexusOpponentLionMan::instance = new HexusOpponentLionMan();
	}

	return HexusOpponentLionMan::instance;
}

HexusOpponentLionMan::HexusOpponentLionMan() : HexusOpponentData(
	EntityResources::Enemies_LionMan_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-24.0f, -24.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentLionMan::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.225f),
	HexusOpponentData::generateDeck(25, 0.225f,
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

HexusOpponentLionMan::~HexusOpponentLionMan()
{
}
