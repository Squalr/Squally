#include "HexusOpponentYeti.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentYeti::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI";
HexusOpponentYeti* HexusOpponentYeti::instance = nullptr;

HexusOpponentYeti* HexusOpponentYeti::getInstance()
{
	if (HexusOpponentYeti::instance == nullptr)
	{
		HexusOpponentYeti::instance = new HexusOpponentYeti();
	}

	return HexusOpponentYeti::instance;
}

HexusOpponentYeti::HexusOpponentYeti() : HexusOpponentData(
	EntityResources::Enemies_BalmerPeaks_Yeti_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.5f,
	Vec2(-48.0f, -72.0f),
	Vec2(-32.0f, -56.0f),
	HexusOpponentYeti::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.61f),
	HexusOpponentData::generateDeck(25, 0.61f,
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

HexusOpponentYeti::~HexusOpponentYeti()
{
}
