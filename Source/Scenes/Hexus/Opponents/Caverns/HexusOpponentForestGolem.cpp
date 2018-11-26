#include "HexusOpponentForestGolem.h"

const std::string HexusOpponentForestGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FOREST_GOLEM";
HexusOpponentForestGolem* HexusOpponentForestGolem::instance = nullptr;

HexusOpponentForestGolem* HexusOpponentForestGolem::getInstance()
{
	if (HexusOpponentForestGolem::instance == nullptr)
	{
		HexusOpponentForestGolem::instance = new HexusOpponentForestGolem();
	}

	return HexusOpponentForestGolem::instance;
}

HexusOpponentForestGolem::HexusOpponentForestGolem() : HexusOpponentData(
	EntityResources::Platformer_Environment_Caverns_Enemies_ForestGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -96.0f),
	Vec2(-48.0f, -16.0f),
	HexusOpponentForestGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.415f),
	HexusOpponentData::generateDeck(25, 0.415f,
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

HexusOpponentForestGolem::~HexusOpponentForestGolem()
{
}
