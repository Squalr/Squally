#include "HexusOpponentTheldar.h"

const std::string HexusOpponentTheldar::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THELDAR";
HexusOpponentTheldar* HexusOpponentTheldar::instance = nullptr;

HexusOpponentTheldar* HexusOpponentTheldar::getInstance()
{
	if (HexusOpponentTheldar::instance == nullptr)
	{
		HexusOpponentTheldar::instance = new HexusOpponentTheldar();
	}

	return HexusOpponentTheldar::instance;
}

HexusOpponentTheldar::HexusOpponentTheldar() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Theldar_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentTheldar::OpponentSaveKey,
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

HexusOpponentTheldar::~HexusOpponentTheldar()
{
}
