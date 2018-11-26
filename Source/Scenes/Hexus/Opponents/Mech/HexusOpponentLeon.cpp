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
	EntityResources::Platformer_Environment_Mech_Npcs_Leon_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentLeon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.94f),
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
