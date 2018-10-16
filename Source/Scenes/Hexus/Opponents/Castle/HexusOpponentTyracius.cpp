#include "HexusOpponentTyracius.h"

const std::string HexusOpponentTyracius::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TYRACIUS";
HexusOpponentTyracius* HexusOpponentTyracius::instance = nullptr;

HexusOpponentTyracius* HexusOpponentTyracius::getInstance()
{
	if (HexusOpponentTyracius::instance == nullptr)
	{
		HexusOpponentTyracius::instance = new HexusOpponentTyracius();
	}

	return HexusOpponentTyracius::instance;
}

HexusOpponentTyracius::HexusOpponentTyracius() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Tyracius_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentTyracius::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.6f,
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

HexusOpponentTyracius::~HexusOpponentTyracius()
{
}
