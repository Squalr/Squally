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
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Rhinoman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -180.0f),
	HexusOpponentRhinoman::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary10),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex9),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal10),
	},
	HexusOpponentData::generateDeck(25, 0.1f,
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
