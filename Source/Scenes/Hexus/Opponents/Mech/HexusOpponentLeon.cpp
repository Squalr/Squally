#include "HexusOpponentLeon.h"

const std::string HexusOpponentLeon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEON";
HexusOpponentLeon* HexusOpponentLeon::instance = nullptr;

HexusOpponentLeon* HexusOpponentLeon::getInstance()
{
	if (HexusOpponentLeon::instance == nullptr)
	{
		HexusOpponentLeon::instance = new HexusOpponentLeon();
	}

	return HexusOpponentLeon::instance;
}

HexusOpponentLeon::HexusOpponentLeon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Npcs_Leon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentLeon::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.94f,
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

HexusOpponentLeon::~HexusOpponentLeon()
{
}
