#include "HexusOpponentToben.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentToben::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOBEN";
HexusOpponentToben* HexusOpponentToben::instance = nullptr;

HexusOpponentToben* HexusOpponentToben::getInstance()
{
	if (HexusOpponentToben::instance == nullptr)
	{
		HexusOpponentToben::instance = new HexusOpponentToben();
	}

	return HexusOpponentToben::instance;
}

HexusOpponentToben::HexusOpponentToben() : HexusOpponentData(
	EntityResources::Npcs_EndianForest_Toben_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentToben::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.31f),
	HexusOpponentData::generateDeck(25, 0.31f,
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentToben::~HexusOpponentToben()
{
}
