#include "HexusOpponentEarthGolem.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentEarthGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EARTH_GOLEM";
HexusOpponentEarthGolem* HexusOpponentEarthGolem::instance = nullptr;

HexusOpponentEarthGolem* HexusOpponentEarthGolem::getInstance()
{
	if (HexusOpponentEarthGolem::instance == nullptr)
	{
		HexusOpponentEarthGolem::instance = new HexusOpponentEarthGolem();
	}

	return HexusOpponentEarthGolem::instance;
}

HexusOpponentEarthGolem::HexusOpponentEarthGolem() : HexusOpponentData(
	EntityResources::Enemies_SeaSharpCaverns_EarthGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-48.0f, -96.0f),
	HexusOpponentEarthGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.425f),
	HexusOpponentData::generateDeck(25, 0.425f,
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

HexusOpponentEarthGolem::~HexusOpponentEarthGolem()
{
}
