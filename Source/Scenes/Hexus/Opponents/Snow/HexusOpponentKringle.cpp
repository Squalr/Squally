#include "HexusOpponentKringle.h"

const std::string HexusOpponentKringle::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KRINGLE";
HexusOpponentKringle* HexusOpponentKringle::instance = nullptr;

HexusOpponentKringle* HexusOpponentKringle::getInstance()
{
	if (HexusOpponentKringle::instance == nullptr)
	{
		HexusOpponentKringle::instance = new HexusOpponentKringle();
	}

	return HexusOpponentKringle::instance;
}

HexusOpponentKringle::HexusOpponentKringle() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Kringle_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentKringle::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.75f,
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

HexusOpponentKringle::~HexusOpponentKringle()
{
}
