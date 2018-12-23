#include "HexusOpponentGoblinShaman.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentGoblinShaman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_SHAMAN";
HexusOpponentGoblinShaman* HexusOpponentGoblinShaman::instance = nullptr;

HexusOpponentGoblinShaman* HexusOpponentGoblinShaman::getInstance()
{
	if (HexusOpponentGoblinShaman::instance == nullptr)
	{
		HexusOpponentGoblinShaman::instance = new HexusOpponentGoblinShaman();
	}

	return HexusOpponentGoblinShaman::instance;
}

HexusOpponentGoblinShaman::HexusOpponentGoblinShaman() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_GoblinShaman_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentGoblinShaman::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.115f),
	HexusOpponentData::generateDeck(25, 0.115f,
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentGoblinShaman::~HexusOpponentGoblinShaman()
{
}
