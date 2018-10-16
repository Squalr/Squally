#include "HexusOpponentAthena.h"

const std::string HexusOpponentAthena::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ATHENA";
HexusOpponentAthena* HexusOpponentAthena::instance = nullptr;

HexusOpponentAthena* HexusOpponentAthena::getInstance()
{
	if (HexusOpponentAthena::instance == nullptr)
	{
		HexusOpponentAthena::instance = new HexusOpponentAthena();
	}

	return HexusOpponentAthena::instance;
}

HexusOpponentAthena::HexusOpponentAthena() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Athena_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAthena::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.4f,
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

HexusOpponentAthena::~HexusOpponentAthena()
{
}
