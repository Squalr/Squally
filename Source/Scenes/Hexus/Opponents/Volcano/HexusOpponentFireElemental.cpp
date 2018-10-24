#include "HexusOpponentFireElemental.h"

const std::string HexusOpponentFireElemental::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FIRE_ELEMENTAL";
HexusOpponentFireElemental* HexusOpponentFireElemental::instance = nullptr;

HexusOpponentFireElemental* HexusOpponentFireElemental::getInstance()
{
	if (HexusOpponentFireElemental::instance == nullptr)
	{
		HexusOpponentFireElemental::instance = new HexusOpponentFireElemental();
	}

	return HexusOpponentFireElemental::instance;
}

HexusOpponentFireElemental::HexusOpponentFireElemental() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Enemies_FireElemental_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -72.0f),
	HexusOpponentFireElemental::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.785f),
	HexusOpponentData::generateDeck(25, 0.785f,
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

HexusOpponentFireElemental::~HexusOpponentFireElemental()
{
}
