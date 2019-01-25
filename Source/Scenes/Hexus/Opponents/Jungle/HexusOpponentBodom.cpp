#include "HexusOpponentBodom.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentBodom::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BODOM";
HexusOpponentBodom* HexusOpponentBodom::instance = nullptr;

HexusOpponentBodom* HexusOpponentBodom::getInstance()
{
	if (HexusOpponentBodom::instance == nullptr)
	{
		HexusOpponentBodom::instance = new HexusOpponentBodom();
	}

	return HexusOpponentBodom::instance;
}

HexusOpponentBodom::HexusOpponentBodom() : HexusOpponentData(
	EntityResources::Npcs_BalmerPeaks_Bodom_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentBodom::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.11f),
	HexusOpponentData::generateDeck(25, 0.11f,
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

HexusOpponentBodom::~HexusOpponentBodom()
{
}
