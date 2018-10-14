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
	Resources::Entities_Platformer_Environment_Ruins_Enemies_TigerMan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-16.0f, -80.0f),
	HexusOpponentTigerMan::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 6, 0.33f, 0.33f,
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
