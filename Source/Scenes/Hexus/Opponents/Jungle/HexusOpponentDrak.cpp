#include "HexusOpponentDrak.h"

const std::string HexusOpponentDrak::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DRAK";
HexusOpponentDrak* HexusOpponentDrak::instance = nullptr;

HexusOpponentDrak* HexusOpponentDrak::getInstance()
{
	if (HexusOpponentDrak::instance == nullptr)
	{
		HexusOpponentDrak::instance = new HexusOpponentDrak();
	}

	return HexusOpponentDrak::instance;
}

HexusOpponentDrak::HexusOpponentDrak() : HexusOpponentData(
	EntityResources::Environment_Jungle_Npcs_Drak_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentDrak::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.13f),
	HexusOpponentData::generateDeck(25, 0.13f,
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

HexusOpponentDrak::~HexusOpponentDrak()
{
}
