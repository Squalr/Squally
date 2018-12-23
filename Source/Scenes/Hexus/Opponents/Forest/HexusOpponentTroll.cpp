#include "HexusOpponentTroll.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentTroll::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TROLL";
HexusOpponentTroll* HexusOpponentTroll::instance = nullptr;

HexusOpponentTroll* HexusOpponentTroll::getInstance()
{
	if (HexusOpponentTroll::instance == nullptr)
	{
		HexusOpponentTroll::instance = new HexusOpponentTroll();
	}

	return HexusOpponentTroll::instance;
}

HexusOpponentTroll::HexusOpponentTroll() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_Troll_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-40.0f, -48.0f),
	HexusOpponentTroll::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.385f),
	HexusOpponentData::generateDeck(25, 0.385f,
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

HexusOpponentTroll::~HexusOpponentTroll()
{
}
