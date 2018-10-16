#include "HexusOpponentPolyphemus.h"

const std::string HexusOpponentPolyphemus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POLYPHEMUS";
HexusOpponentPolyphemus* HexusOpponentPolyphemus::instance = nullptr;

HexusOpponentPolyphemus* HexusOpponentPolyphemus::getInstance()
{
	if (HexusOpponentPolyphemus::instance == nullptr)
	{
		HexusOpponentPolyphemus::instance = new HexusOpponentPolyphemus();
	}

	return HexusOpponentPolyphemus::instance;
}

HexusOpponentPolyphemus::HexusOpponentPolyphemus() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Polyphemus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPolyphemus::OpponentSaveKey,
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

HexusOpponentPolyphemus::~HexusOpponentPolyphemus()
{
}
