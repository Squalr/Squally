#include "HexusOpponentOsiris.h"

const std::string HexusOpponentOsiris::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_OSIRIS";
HexusOpponentOsiris* HexusOpponentOsiris::instance = nullptr;

HexusOpponentOsiris* HexusOpponentOsiris::getInstance()
{
	if (HexusOpponentOsiris::instance == nullptr)
	{
		HexusOpponentOsiris::instance = new HexusOpponentOsiris();
	}

	return HexusOpponentOsiris::instance;
}

HexusOpponentOsiris::HexusOpponentOsiris() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Osiris_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -72.0f),
	HexusOpponentOsiris::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 7, 0.33f, 0.33f,
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

HexusOpponentOsiris::~HexusOpponentOsiris()
{
}
