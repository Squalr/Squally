#include "HexusOpponentPrincessMittens.h"

const std::string HexusOpponentPrincessMittens::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MITTENS";
HexusOpponentPrincessMittens* HexusOpponentPrincessMittens::instance = nullptr;

HexusOpponentPrincessMittens* HexusOpponentPrincessMittens::getInstance()
{
	if (HexusOpponentPrincessMittens::instance == nullptr)
	{
		HexusOpponentPrincessMittens::instance = new HexusOpponentPrincessMittens();
	}

	return HexusOpponentPrincessMittens::instance;
}

HexusOpponentPrincessMittens::HexusOpponentPrincessMittens() : HexusOpponentData(
	EntityResources::Platformer_Environment_Forest_Npcs_PrincessMittens_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentPrincessMittens::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.39f),
	HexusOpponentData::generateDeck(25, 0.39f,
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

HexusOpponentPrincessMittens::~HexusOpponentPrincessMittens()
{
}
