#include "HexusOpponentCyclops.h"

const std::string HexusOpponentCyclops::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CYCLOPS";
HexusOpponentCyclops* HexusOpponentCyclops::instance = nullptr;

HexusOpponentCyclops* HexusOpponentCyclops::getInstance()
{
	if (HexusOpponentCyclops::instance == nullptr)
	{
		HexusOpponentCyclops::instance = new HexusOpponentCyclops();
	}

	return HexusOpponentCyclops::instance;
}

HexusOpponentCyclops::HexusOpponentCyclops() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_Cyclops_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-40.0f, -48.0f),
	HexusOpponentCyclops::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.45f,
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

HexusOpponentCyclops::~HexusOpponentCyclops()
{
}
