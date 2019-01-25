#include "HexusOpponentIceGolem.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentIceGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ICE_GOLEM";
HexusOpponentIceGolem* HexusOpponentIceGolem::instance = nullptr;

HexusOpponentIceGolem* HexusOpponentIceGolem::getInstance()
{
	if (HexusOpponentIceGolem::instance == nullptr)
	{
		HexusOpponentIceGolem::instance = new HexusOpponentIceGolem();
	}

	return HexusOpponentIceGolem::instance;
}

HexusOpponentIceGolem::HexusOpponentIceGolem() : HexusOpponentData(
	EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-48.0f, -80.0f),
	HexusOpponentIceGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.66f),
	HexusOpponentData::generateDeck(25, 0.66f,
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

HexusOpponentIceGolem::~HexusOpponentIceGolem()
{
}
