#include "HexusOpponentScarecrow.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentScarecrow::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCARECROW";
HexusOpponentScarecrow* HexusOpponentScarecrow::instance = nullptr;

HexusOpponentScarecrow* HexusOpponentScarecrow::getInstance()
{
	if (HexusOpponentScarecrow::instance == nullptr)
	{
		HexusOpponentScarecrow::instance = new HexusOpponentScarecrow();
	}

	return HexusOpponentScarecrow::instance;
}

HexusOpponentScarecrow::HexusOpponentScarecrow() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Scarecrow_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -96.0f),
	Vec2(-16.0f, -128.0f),
	HexusOpponentScarecrow::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.585f),
	HexusOpponentData::generateDeck(25, 0.585f,
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

HexusOpponentScarecrow::~HexusOpponentScarecrow()
{
}
