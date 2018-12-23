#include "HexusOpponentWraith.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentWraith::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WRAITH";
HexusOpponentWraith* HexusOpponentWraith::instance = nullptr;

HexusOpponentWraith* HexusOpponentWraith::getInstance()
{
	if (HexusOpponentWraith::instance == nullptr)
	{
		HexusOpponentWraith::instance = new HexusOpponentWraith();
	}

	return HexusOpponentWraith::instance;
}

HexusOpponentWraith::HexusOpponentWraith() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Wraith_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.7f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentWraith::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.505f),
	HexusOpponentData::generateDeck(25, 0.505f,
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

HexusOpponentWraith::~HexusOpponentWraith()
{
}
