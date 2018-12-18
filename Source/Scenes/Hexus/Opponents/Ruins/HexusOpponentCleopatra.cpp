#include "HexusOpponentCleopatra.h"

const std::string HexusOpponentCleopatra::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CLEOPATRA";
HexusOpponentCleopatra* HexusOpponentCleopatra::instance = nullptr;

HexusOpponentCleopatra* HexusOpponentCleopatra::getInstance()
{
	if (HexusOpponentCleopatra::instance == nullptr)
	{
		HexusOpponentCleopatra::instance = new HexusOpponentCleopatra();
	}

	return HexusOpponentCleopatra::instance;
}

HexusOpponentCleopatra::HexusOpponentCleopatra() : HexusOpponentData(
	EntityResources::Npcs_UnderflowRuins_Cleopatra_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentCleopatra::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.295f),
	HexusOpponentData::generateDeck(25, 0.295f,
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

HexusOpponentCleopatra::~HexusOpponentCleopatra()
{
}
