#include "HexusOpponentThor.h"

const std::string HexusOpponentThor::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THOR";
HexusOpponentThor* HexusOpponentThor::instance = nullptr;

HexusOpponentThor* HexusOpponentThor::getInstance()
{
	if (HexusOpponentThor::instance == nullptr)
	{
		HexusOpponentThor::instance = new HexusOpponentThor();
	}

	return HexusOpponentThor::instance;
}

HexusOpponentThor::HexusOpponentThor() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Thor_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentThor::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.18f),
	HexusOpponentData::generateDeck(25, 0.18f,
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

HexusOpponentThor::~HexusOpponentThor()
{
}
