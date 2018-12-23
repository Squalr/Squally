#include "HexusOpponentCyclops.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

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
	EntityResources::Enemies_EndianForest_Cyclops_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-40.0f, -48.0f),
	HexusOpponentCyclops::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.395f),
	HexusOpponentData::generateDeck(25, 0.395f,
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

HexusOpponentCyclops::~HexusOpponentCyclops()
{
}
