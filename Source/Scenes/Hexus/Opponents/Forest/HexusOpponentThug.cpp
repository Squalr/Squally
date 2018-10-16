#include "HexusOpponentThug.h"

const std::string HexusOpponentThug::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THUG";
HexusOpponentThug* HexusOpponentThug::instance = nullptr;

HexusOpponentThug* HexusOpponentThug::getInstance()
{
	if (HexusOpponentThug::instance == nullptr)
	{
		HexusOpponentThug::instance = new HexusOpponentThug();
	}

	return HexusOpponentThug::instance;
}

HexusOpponentThug::HexusOpponentThug() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_Thug_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentThug::OpponentSaveKey,
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

HexusOpponentThug::~HexusOpponentThug()
{
}
