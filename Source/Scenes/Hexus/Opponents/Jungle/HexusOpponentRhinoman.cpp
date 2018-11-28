#include "HexusOpponentRhinoman.h"

const std::string HexusOpponentRhinoman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RHINOMAN";
HexusOpponentRhinoman* HexusOpponentRhinoman::instance = nullptr;

HexusOpponentRhinoman* HexusOpponentRhinoman::getInstance()
{
	if (HexusOpponentRhinoman::instance == nullptr)
	{
		HexusOpponentRhinoman::instance = new HexusOpponentRhinoman();
	}

	return HexusOpponentRhinoman::instance;
}

HexusOpponentRhinoman::HexusOpponentRhinoman() : HexusOpponentData(
	EntityResources::Environment_Jungle_Enemies_Rhinoman_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -180.0f),
	HexusOpponentRhinoman::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.22f),
	HexusOpponentData::generateDeck(25, 0.22f,
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

HexusOpponentRhinoman::~HexusOpponentRhinoman()
{
}
