#include "HexusOpponentUndead.h"

const std::string HexusOpponentUndead::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_UNDEAD";
HexusOpponentUndead* HexusOpponentUndead::instance = nullptr;

HexusOpponentUndead* HexusOpponentUndead::getInstance()
{
	if (HexusOpponentUndead::instance == nullptr)
	{
		HexusOpponentUndead::instance = new HexusOpponentUndead();
	}

	return HexusOpponentUndead::instance;
}

HexusOpponentUndead::HexusOpponentUndead() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_Undead_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentUndead::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.835f,
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

HexusOpponentUndead::~HexusOpponentUndead()
{
}
