#include "HexusOpponentViper.h"

const std::string HexusOpponentViper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIPER";
HexusOpponentViper* HexusOpponentViper::instance = nullptr;

HexusOpponentViper* HexusOpponentViper::getInstance()
{
	if (HexusOpponentViper::instance == nullptr)
	{
		HexusOpponentViper::instance = new HexusOpponentViper();
	}

	return HexusOpponentViper::instance;
}

HexusOpponentViper::HexusOpponentViper() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Viper_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentViper::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 12, 0.33f, 0.33f,
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

HexusOpponentViper::~HexusOpponentViper()
{
}
