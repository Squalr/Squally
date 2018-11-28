#include "HexusOpponentRaka.h"

const std::string HexusOpponentRaka::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAKA";
HexusOpponentRaka* HexusOpponentRaka::instance = nullptr;

HexusOpponentRaka* HexusOpponentRaka::getInstance()
{
	if (HexusOpponentRaka::instance == nullptr)
	{
		HexusOpponentRaka::instance = new HexusOpponentRaka();
	}

	return HexusOpponentRaka::instance;
}

HexusOpponentRaka::HexusOpponentRaka() : HexusOpponentData(
	EntityResources::Environment_Jungle_Npcs_Raka_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentRaka::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.155f),
	HexusOpponentData::generateDeck(25, 0.155f,
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

HexusOpponentRaka::~HexusOpponentRaka()
{
}
