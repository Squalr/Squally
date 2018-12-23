#include "HexusOpponentKrampus.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentKrampus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KRAMPUS";
HexusOpponentKrampus* HexusOpponentKrampus::instance = nullptr;

HexusOpponentKrampus* HexusOpponentKrampus::getInstance()
{
	if (HexusOpponentKrampus::instance == nullptr)
	{
		HexusOpponentKrampus::instance = new HexusOpponentKrampus();
	}

	return HexusOpponentKrampus::instance;
}

HexusOpponentKrampus::HexusOpponentKrampus() : HexusOpponentData(
	EntityResources::Enemies_SeaSharpCaverns_Krampus_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.85f,
	Vec2(-32.0f, -32.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentKrampus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.52f),
	HexusOpponentData::generateDeck(25, 0.52f,
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

HexusOpponentKrampus::~HexusOpponentKrampus()
{
}
