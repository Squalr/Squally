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
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.54f),
	HexusOpponentData::generateDeck(25, 0.54f,
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
