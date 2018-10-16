#include "HexusOpponentSanta.h"

const std::string HexusOpponentSanta::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SANTA";
HexusOpponentSanta* HexusOpponentSanta::instance = nullptr;

HexusOpponentSanta* HexusOpponentSanta::getInstance()
{
	if (HexusOpponentSanta::instance == nullptr)
	{
		HexusOpponentSanta::instance = new HexusOpponentSanta();
	}

	return HexusOpponentSanta::instance;
}

HexusOpponentSanta::HexusOpponentSanta() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_Santa_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentSanta::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.715f,
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

HexusOpponentSanta::~HexusOpponentSanta()
{
}
