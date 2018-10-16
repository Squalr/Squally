#include "HexusOpponentPenguinGrunt.h"

const std::string HexusOpponentPenguinGrunt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PENGUIN_GRUNT";
HexusOpponentPenguinGrunt* HexusOpponentPenguinGrunt::instance = nullptr;

HexusOpponentPenguinGrunt* HexusOpponentPenguinGrunt::getInstance()
{
	if (HexusOpponentPenguinGrunt::instance == nullptr)
	{
		HexusOpponentPenguinGrunt::instance = new HexusOpponentPenguinGrunt();
	}

	return HexusOpponentPenguinGrunt::instance;
}

HexusOpponentPenguinGrunt::HexusOpponentPenguinGrunt() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_PenguinGrunt_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentPenguinGrunt::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.62f,
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

HexusOpponentPenguinGrunt::~HexusOpponentPenguinGrunt()
{
}
