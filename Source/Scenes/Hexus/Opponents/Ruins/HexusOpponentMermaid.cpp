#include "HexusOpponentMermaid.h"

const std::string HexusOpponentMermaid::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MERMAID";
HexusOpponentMermaid* HexusOpponentMermaid::instance = nullptr;

HexusOpponentMermaid* HexusOpponentMermaid::getInstance()
{
	if (HexusOpponentMermaid::instance == nullptr)
	{
		HexusOpponentMermaid::instance = new HexusOpponentMermaid();
	}

	return HexusOpponentMermaid::instance;
}

HexusOpponentMermaid::HexusOpponentMermaid() : HexusOpponentData(
	EntityResources::Platformer_Environment_Ruins_Enemies_Mermaid_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -144.0f),
	Vec2(0.0f, -160.0f),
	HexusOpponentMermaid::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.27f),
	HexusOpponentData::generateDeck(25, 0.27f,
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

HexusOpponentMermaid::~HexusOpponentMermaid()
{
}
