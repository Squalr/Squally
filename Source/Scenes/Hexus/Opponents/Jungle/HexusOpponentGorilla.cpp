#include "HexusOpponentGorilla.h"

const std::string HexusOpponentGorilla::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GORILLA";
HexusOpponentGorilla* HexusOpponentGorilla::instance = nullptr;

HexusOpponentGorilla* HexusOpponentGorilla::getInstance()
{
	if (HexusOpponentGorilla::instance == nullptr)
	{
		HexusOpponentGorilla::instance = new HexusOpponentGorilla();
	}

	return HexusOpponentGorilla::instance;
}

HexusOpponentGorilla::HexusOpponentGorilla() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Gorilla_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-80.0f, -32.0f),
	HexusOpponentGorilla::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
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

HexusOpponentGorilla::~HexusOpponentGorilla()
{
}
