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
	EntityResources::Enemies_RoboGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.7f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -128.0f),
	HexusOpponentRoboGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.975f),
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
