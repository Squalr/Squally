#include "HexusOpponentAtreus.h"

const std::string HexusOpponentAtreus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ATREUS";
HexusOpponentAtreus* HexusOpponentAtreus::instance = nullptr;

HexusOpponentAtreus* HexusOpponentAtreus::getInstance()
{
	if (HexusOpponentAtreus::instance == nullptr)
	{
		HexusOpponentAtreus::instance = new HexusOpponentAtreus();
	}

	return HexusOpponentAtreus::instance;
}

HexusOpponentAtreus::HexusOpponentAtreus() : HexusOpponentData(
	EntityResources::Npcs_Atreus_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAtreus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.96f),
	HexusOpponentData::generateDeck(25, 0.96f,
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

HexusOpponentAtreus::~HexusOpponentAtreus()
{
}
