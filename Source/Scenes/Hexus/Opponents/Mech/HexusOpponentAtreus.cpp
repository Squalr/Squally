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
	Resources::Entities_Platformer_Environment_Mech_Npcs_Atreus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAtreus::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
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

HexusOpponentAtreus::~HexusOpponentAtreus()
{
}
