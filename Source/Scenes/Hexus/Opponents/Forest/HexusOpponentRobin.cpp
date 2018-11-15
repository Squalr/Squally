#include "HexusOpponentRobin.h"

const std::string HexusOpponentRobin::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROBIN";
HexusOpponentRobin* HexusOpponentRobin::instance = nullptr;

HexusOpponentRobin* HexusOpponentRobin::getInstance()
{
	if (HexusOpponentRobin::instance == nullptr)
	{
		HexusOpponentRobin::instance = new HexusOpponentRobin();
	}

	return HexusOpponentRobin::instance;
}

HexusOpponentRobin::HexusOpponentRobin() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Robin_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentRobin::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.36f),
	HexusOpponentData::generateDeck(25, 0.36f,
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

HexusOpponentRobin::~HexusOpponentRobin()
{
}
