#include "HexusOpponentViking.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentViking::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIKING";
HexusOpponentViking* HexusOpponentViking::instance = nullptr;

HexusOpponentViking* HexusOpponentViking::getInstance()
{
	if (HexusOpponentViking::instance == nullptr)
	{
		HexusOpponentViking::instance = new HexusOpponentViking();
	}

	return HexusOpponentViking::instance;
}

HexusOpponentViking::HexusOpponentViking() : HexusOpponentData(
	EntityResources::Enemies_VoidStar_Viking_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentViking::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.185f),
	HexusOpponentData::generateDeck(25, 0.185f,
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

HexusOpponentViking::~HexusOpponentViking()
{
}
