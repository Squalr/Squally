#include "HexusOpponentDemonShaman.h"

const std::string HexusOpponentDemonShaman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SHAMAN";
HexusOpponentDemonShaman* HexusOpponentDemonShaman::instance = nullptr;

HexusOpponentDemonShaman* HexusOpponentDemonShaman::getInstance()
{
	if (HexusOpponentDemonShaman::instance == nullptr)
	{
		HexusOpponentDemonShaman::instance = new HexusOpponentDemonShaman();
	}

	return HexusOpponentDemonShaman::instance;
}

HexusOpponentDemonShaman::HexusOpponentDemonShaman() : HexusOpponentData(
	EntityResources::Platformer_Environment_Volcano_Enemies_DemonShaman_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentDemonShaman::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.735f),
	HexusOpponentData::generateDeck(25, 0.735f,
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

HexusOpponentDemonShaman::~HexusOpponentDemonShaman()
{
}
