#include "HexusOpponentShade.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentShade::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHADE";
HexusOpponentShade* HexusOpponentShade::instance = nullptr;

HexusOpponentShade* HexusOpponentShade::getInstance()
{
	if (HexusOpponentShade::instance == nullptr)
	{
		HexusOpponentShade::instance = new HexusOpponentShade();
	}

	return HexusOpponentShade::instance;
}

HexusOpponentShade::HexusOpponentShade() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Shade_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -96.0f),
	Vec2(-16.0f, -128.0f),
	HexusOpponentShade::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.595f),
	HexusOpponentData::generateDeck(25, 0.595f,
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

HexusOpponentShade::~HexusOpponentShade()
{
}
