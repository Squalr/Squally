#include "HexusOpponentTigerMan.h"

const std::string HexusOpponentTigerMan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIGER_MAN";
HexusOpponentTigerMan* HexusOpponentTigerMan::instance = nullptr;

HexusOpponentTigerMan* HexusOpponentTigerMan::getInstance()
{
	if (HexusOpponentTigerMan::instance == nullptr)
	{
		HexusOpponentTigerMan::instance = new HexusOpponentTigerMan();
	}

	return HexusOpponentTigerMan::instance;
}

HexusOpponentTigerMan::HexusOpponentTigerMan() : HexusOpponentData(
	EntityResources::Environment_Ruins_Enemies_TigerMan_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-16.0f, -80.0f),
	HexusOpponentTigerMan::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.245f),
	HexusOpponentData::generateDeck(25, 0.245f,
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

HexusOpponentTigerMan::~HexusOpponentTigerMan()
{
}
