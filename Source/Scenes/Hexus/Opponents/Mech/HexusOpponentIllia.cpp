#include "HexusOpponentIllia.h"

const std::string HexusOpponentIllia::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ILLIA";
HexusOpponentIllia* HexusOpponentIllia::instance = nullptr;

HexusOpponentIllia* HexusOpponentIllia::getInstance()
{
	if (HexusOpponentIllia::instance == nullptr)
	{
		HexusOpponentIllia::instance = new HexusOpponentIllia();
	}

	return HexusOpponentIllia::instance;
}

HexusOpponentIllia::HexusOpponentIllia() : HexusOpponentData(
	EntityResources::Environment_Mech_Npcs_Illia_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentIllia::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.93f),
	HexusOpponentData::generateDeck(25, 0.93f,
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

HexusOpponentIllia::~HexusOpponentIllia()
{
}
