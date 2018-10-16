#include "HexusOpponentLeroy.h"

const std::string HexusOpponentLeroy::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEROY";
HexusOpponentLeroy* HexusOpponentLeroy::instance = nullptr;

HexusOpponentLeroy* HexusOpponentLeroy::getInstance()
{
	if (HexusOpponentLeroy::instance == nullptr)
	{
		HexusOpponentLeroy::instance = new HexusOpponentLeroy();
	}

	return HexusOpponentLeroy::instance;
}

HexusOpponentLeroy::HexusOpponentLeroy() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Leroy_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-64.0f, -112.0f),
	Vec2(-16.0f, -96.0f),
	HexusOpponentLeroy::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.51f,
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

HexusOpponentLeroy::~HexusOpponentLeroy()
{
}
