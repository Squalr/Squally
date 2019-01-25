#include "HexusOpponentAspen.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentAspen::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASPEN";
HexusOpponentAspen* HexusOpponentAspen::instance = nullptr;

HexusOpponentAspen* HexusOpponentAspen::getInstance()
{
	if (HexusOpponentAspen::instance == nullptr)
	{
		HexusOpponentAspen::instance = new HexusOpponentAspen();
	}

	return HexusOpponentAspen::instance;
}

HexusOpponentAspen::HexusOpponentAspen() : HexusOpponentData(
	EntityResources::Npcs_BalmerPeaks_Aspen_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-24.0f, -32.0f),
	HexusOpponentAspen::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.615f),
	HexusOpponentData::generateDeck(25, 0.615f,
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

HexusOpponentAspen::~HexusOpponentAspen()
{
}
