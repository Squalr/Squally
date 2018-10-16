#include "HexusOpponentRoboGolem.h"

const std::string HexusOpponentRoboGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROBO_GOLEM";
HexusOpponentRoboGolem* HexusOpponentRoboGolem::instance = nullptr;

HexusOpponentRoboGolem* HexusOpponentRoboGolem::getInstance()
{
	if (HexusOpponentRoboGolem::instance == nullptr)
	{
		HexusOpponentRoboGolem::instance = new HexusOpponentRoboGolem();
	}

	return HexusOpponentRoboGolem::instance;
}

HexusOpponentRoboGolem::HexusOpponentRoboGolem() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Enemies_RoboGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.7f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -128.0f),
	HexusOpponentRoboGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.975f,
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

HexusOpponentRoboGolem::~HexusOpponentRoboGolem()
{
}
