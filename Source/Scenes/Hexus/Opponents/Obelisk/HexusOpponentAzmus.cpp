#include "HexusOpponentAzmus.h"

const std::string HexusOpponentAzmus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AZMUS";
HexusOpponentAzmus* HexusOpponentAzmus::instance = nullptr;

HexusOpponentAzmus* HexusOpponentAzmus::getInstance()
{
	if (HexusOpponentAzmus::instance == nullptr)
	{
		HexusOpponentAzmus::instance = new HexusOpponentAzmus();
	}

	return HexusOpponentAzmus::instance;
}

HexusOpponentAzmus::HexusOpponentAzmus() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Azmus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentAzmus::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.8f,
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

HexusOpponentAzmus::~HexusOpponentAzmus()
{
}
