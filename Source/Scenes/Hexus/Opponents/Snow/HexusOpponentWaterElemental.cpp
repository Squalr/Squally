#include "HexusOpponentWaterElemental.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentWaterElemental::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WATER_ELEMENTAL";
HexusOpponentWaterElemental* HexusOpponentWaterElemental::instance = nullptr;

HexusOpponentWaterElemental* HexusOpponentWaterElemental::getInstance()
{
	if (HexusOpponentWaterElemental::instance == nullptr)
	{
		HexusOpponentWaterElemental::instance = new HexusOpponentWaterElemental();
	}

	return HexusOpponentWaterElemental::instance;
}

HexusOpponentWaterElemental::HexusOpponentWaterElemental() : HexusOpponentData(
	EntityResources::Enemies_LambdaPeaks_WaterElemental_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -72.0f),
	HexusOpponentWaterElemental::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.68f),
	HexusOpponentData::generateDeck(25, 0.68f,
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

HexusOpponentWaterElemental::~HexusOpponentWaterElemental()
{
}
