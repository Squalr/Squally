#include "HexusOpponentExterminator.h"

const std::string HexusOpponentExterminator::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXTERMINATOR";
HexusOpponentExterminator* HexusOpponentExterminator::instance = nullptr;

HexusOpponentExterminator* HexusOpponentExterminator::getInstance()
{
	if (HexusOpponentExterminator::instance == nullptr)
	{
		HexusOpponentExterminator::instance = new HexusOpponentExterminator();
	}

	return HexusOpponentExterminator::instance;
}

HexusOpponentExterminator::HexusOpponentExterminator() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Enemies_Exterminator_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -64.0f),
	HexusOpponentExterminator::OpponentSaveKey,
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

HexusOpponentExterminator::~HexusOpponentExterminator()
{
}
