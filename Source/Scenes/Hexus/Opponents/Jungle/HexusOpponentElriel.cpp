#include "HexusOpponentElriel.h"

const std::string HexusOpponentElriel::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ELRIEL";
HexusOpponentElriel* HexusOpponentElriel::instance = nullptr;

HexusOpponentElriel* HexusOpponentElriel::getInstance()
{
	if (HexusOpponentElriel::instance == nullptr)
	{
		HexusOpponentElriel::instance = new HexusOpponentElriel();
	}

	return HexusOpponentElriel::instance;
}

HexusOpponentElriel::HexusOpponentElriel() : HexusOpponentData(
	EntityResources::Platformer_Environment_Jungle_Npcs_Elriel_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentElriel::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.12f),
	HexusOpponentData::generateDeck(25, 0.12f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentElriel::~HexusOpponentElriel()
{
}
