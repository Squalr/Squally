#include "HexusOpponentCeleste.h"

const std::string HexusOpponentCeleste::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CELESTE";
HexusOpponentCeleste* HexusOpponentCeleste::instance = nullptr;

HexusOpponentCeleste* HexusOpponentCeleste::getInstance()
{
	if (HexusOpponentCeleste::instance == nullptr)
	{
		HexusOpponentCeleste::instance = new HexusOpponentCeleste();
	}

	return HexusOpponentCeleste::instance;
}

HexusOpponentCeleste::HexusOpponentCeleste() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Celeste_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCeleste::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 11, 0.33f, 0.33f,
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

HexusOpponentCeleste::~HexusOpponentCeleste()
{
}
