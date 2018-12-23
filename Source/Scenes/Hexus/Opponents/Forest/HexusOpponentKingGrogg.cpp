#include "HexusOpponentKingGrogg.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentKingGrogg::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_GROGG";
HexusOpponentKingGrogg* HexusOpponentKingGrogg::instance = nullptr;

HexusOpponentKingGrogg* HexusOpponentKingGrogg::getInstance()
{
	if (HexusOpponentKingGrogg::instance == nullptr)
	{
		HexusOpponentKingGrogg::instance = new HexusOpponentKingGrogg();
	}

	return HexusOpponentKingGrogg::instance;
}

HexusOpponentKingGrogg::HexusOpponentKingGrogg() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_KingGrogg_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -112.0f),
	HexusOpponentKingGrogg::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.42f),
	HexusOpponentData::generateDeck(25, 0.42f,
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

HexusOpponentKingGrogg::~HexusOpponentKingGrogg()
{
}
