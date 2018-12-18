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
	EntityResources::Npcs_Athena_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAthena::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.23f),
	HexusOpponentData::generateDeck(25, 0.23f,
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
