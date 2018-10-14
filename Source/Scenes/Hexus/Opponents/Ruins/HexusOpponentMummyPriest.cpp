#include "HexusOpponentMummyPriest.h"

const std::string HexusOpponentMummyPriest::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_PRIEST";
HexusOpponentMummyPriest* HexusOpponentMummyPriest::instance = nullptr;

HexusOpponentMummyPriest* HexusOpponentMummyPriest::getInstance()
{
	if (HexusOpponentMummyPriest::instance == nullptr)
	{
		HexusOpponentMummyPriest::instance = new HexusOpponentMummyPriest();
	}

	return HexusOpponentMummyPriest::instance;
}

HexusOpponentMummyPriest::HexusOpponentMummyPriest() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_MummyPriest_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentMummyPriest::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 6, 0.33f, 0.33f,
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

HexusOpponentMummyPriest::~HexusOpponentMummyPriest()
{
}
