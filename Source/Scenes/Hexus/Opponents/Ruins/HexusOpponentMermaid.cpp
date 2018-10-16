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
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Mermaid_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -144.0f),
	Vec2(0.0f, -160.0f),
	HexusOpponentMermaid::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.4f,
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
