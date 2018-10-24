#include "HexusOpponentRupert.h"

const std::string HexusOpponentRupert::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RUPERT";
HexusOpponentRupert* HexusOpponentRupert::instance = nullptr;

HexusOpponentRupert* HexusOpponentRupert::getInstance()
{
	if (HexusOpponentRupert::instance == nullptr)
	{
		HexusOpponentRupert::instance = new HexusOpponentRupert();
	}

	return HexusOpponentRupert::instance;
}

HexusOpponentRupert::HexusOpponentRupert() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Rupert_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -72.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentRupert::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.37f),
	HexusOpponentData::generateDeck(25, 0.37f,
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

HexusOpponentRupert::~HexusOpponentRupert()
{
}
