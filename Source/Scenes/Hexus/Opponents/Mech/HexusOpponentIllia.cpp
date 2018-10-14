#include "HexusOpponentIllia.h"

const std::string HexusOpponentIllia::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ILLIA";
HexusOpponentIllia* HexusOpponentIllia::instance = nullptr;

HexusOpponentIllia* HexusOpponentIllia::getInstance()
{
	if (HexusOpponentIllia::instance == nullptr)
	{
		HexusOpponentIllia::instance = new HexusOpponentIllia();
	}

	return HexusOpponentIllia::instance;
}

HexusOpponentIllia::HexusOpponentIllia() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Npcs_Illia_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentIllia::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 14, 0.33f, 0.33f,
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

HexusOpponentIllia::~HexusOpponentIllia()
{
}
