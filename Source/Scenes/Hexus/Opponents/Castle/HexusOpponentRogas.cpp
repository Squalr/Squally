#include "HexusOpponentRogas.h"

const std::string HexusOpponentRogas::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROGAS";
HexusOpponentRogas* HexusOpponentRogas::instance = nullptr;

HexusOpponentRogas* HexusOpponentRogas::getInstance()
{
	if (HexusOpponentRogas::instance == nullptr)
	{
		HexusOpponentRogas::instance = new HexusOpponentRogas();
	}

	return HexusOpponentRogas::instance;
}

HexusOpponentRogas::HexusOpponentRogas() : HexusOpponentData(
	EntityResources::Platformer_Environment_Castle_Npcs_Rogas_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentRogas::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.53f),
	HexusOpponentData::generateDeck(25, 0.53f,
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

HexusOpponentRogas::~HexusOpponentRogas()
{
}
