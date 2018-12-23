#include "HexusOpponentKingRedsong.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentKingRedsong::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG";
HexusOpponentKingRedsong* HexusOpponentKingRedsong::instance = nullptr;

HexusOpponentKingRedsong* HexusOpponentKingRedsong::getInstance()
{
	if (HexusOpponentKingRedsong::instance == nullptr)
	{
		HexusOpponentKingRedsong::instance = new HexusOpponentKingRedsong();
	}

	return HexusOpponentKingRedsong::instance;
}

HexusOpponentKingRedsong::HexusOpponentKingRedsong() : HexusOpponentData(
	EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentKingRedsong::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.6f),
	HexusOpponentData::generateDeck(25, 0.6f,
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

HexusOpponentKingRedsong::~HexusOpponentKingRedsong()
{
}
