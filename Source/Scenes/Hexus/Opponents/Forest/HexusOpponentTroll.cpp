#include "HexusOpponentTroll.h"

const std::string HexusOpponentTroll::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TROLL";
HexusOpponentTroll* HexusOpponentTroll::instance = nullptr;

HexusOpponentTroll* HexusOpponentTroll::getInstance()
{
	if (HexusOpponentTroll::instance == nullptr)
	{
		HexusOpponentTroll::instance = new HexusOpponentTroll();
	}

	return HexusOpponentTroll::instance;
}

HexusOpponentTroll::HexusOpponentTroll() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_Troll_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-40.0f, -48.0f),
	HexusOpponentTroll::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 7, 0.33f, 0.33f,
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

HexusOpponentTroll::~HexusOpponentTroll()
{
}
