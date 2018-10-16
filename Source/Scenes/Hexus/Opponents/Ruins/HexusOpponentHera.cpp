#include "HexusOpponentHera.h"

const std::string HexusOpponentHera::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HERA";
HexusOpponentHera* HexusOpponentHera::instance = nullptr;

HexusOpponentHera* HexusOpponentHera::getInstance()
{
	if (HexusOpponentHera::instance == nullptr)
	{
		HexusOpponentHera::instance = new HexusOpponentHera();
	}

	return HexusOpponentHera::instance;
}

HexusOpponentHera::HexusOpponentHera() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Hera_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentHera::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.24f,
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

HexusOpponentHera::~HexusOpponentHera()
{
}
