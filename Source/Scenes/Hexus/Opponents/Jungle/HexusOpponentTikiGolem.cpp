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
	Resources::Entities_Platformer_Environment_Jungle_Enemies_TikiGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -160.0f),
	Vec2(-16.0f, -128.0f),
	HexusOpponentTikiGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary9),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex10),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
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

HexusOpponentTikiGolem::~HexusOpponentTikiGolem()
{
}
