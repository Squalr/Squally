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
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonShaman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentDemonShaman::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
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
