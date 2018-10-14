#include "HexusOpponentGenie.h"

const std::string HexusOpponentGenie::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GENIE";
HexusOpponentGenie* HexusOpponentGenie::instance = nullptr;

HexusOpponentGenie* HexusOpponentGenie::getInstance()
{
	if (HexusOpponentGenie::instance == nullptr)
	{
		HexusOpponentGenie::instance = new HexusOpponentGenie();
	}

	return HexusOpponentGenie::instance;
}

HexusOpponentGenie::HexusOpponentGenie() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_Genie_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.3f,
	Vec2(-32.0f, -160.0f),
	Vec2(-16.0f, -192.0f),
	HexusOpponentGenie::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0, 8, 0.33f, 0.33f,
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

HexusOpponentGenie::~HexusOpponentGenie()
{
}
