#include "HexusOpponentGeryon.h"

const std::string HexusOpponentGeryon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GERYON";
HexusOpponentGeryon* HexusOpponentGeryon::instance = nullptr;

HexusOpponentGeryon* HexusOpponentGeryon::getInstance()
{
	if (HexusOpponentGeryon::instance == nullptr)
	{
		HexusOpponentGeryon::instance = new HexusOpponentGeryon();
	}

	return HexusOpponentGeryon::instance;
}

HexusOpponentGeryon::HexusOpponentGeryon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Geryon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGeryon::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.25f),
	HexusOpponentData::generateDeck(25, 0.25f,
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

HexusOpponentGeryon::~HexusOpponentGeryon()
{
}
