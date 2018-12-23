#include "HexusOpponentThug.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

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
	EntityResources::Enemies_VoidStar_Thug_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentThug::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.305f),
	HexusOpponentData::generateDeck(25, 0.305f,
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

HexusOpponentThug::~HexusOpponentThug()
{
}
