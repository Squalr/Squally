#include "HexusOpponentTikiGolem.h"

const std::string HexusOpponentTikiGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIKI_GOLEM";
HexusOpponentTikiGolem* HexusOpponentTikiGolem::instance = nullptr;

HexusOpponentTikiGolem* HexusOpponentTikiGolem::getInstance()
{
	if (HexusOpponentTikiGolem::instance == nullptr)
	{
		HexusOpponentTikiGolem::instance = new HexusOpponentTikiGolem();
	}

	return HexusOpponentTikiGolem::instance;
}

HexusOpponentTikiGolem::HexusOpponentTikiGolem() : HexusOpponentData(
	EntityResources::Environment_Jungle_Enemies_TikiGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -160.0f),
	Vec2(-16.0f, -128.0f),
	HexusOpponentTikiGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.19f),
	HexusOpponentData::generateDeck(25, 0.19f,
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

HexusOpponentTikiGolem::~HexusOpponentTikiGolem()
{
}
