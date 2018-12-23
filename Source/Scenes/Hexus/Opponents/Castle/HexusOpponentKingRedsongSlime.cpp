#include "HexusOpponentKingRedsongSlime.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentKingRedsongSlime::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG_SLIME";
HexusOpponentKingRedsongSlime* HexusOpponentKingRedsongSlime::instance = nullptr;

HexusOpponentKingRedsongSlime* HexusOpponentKingRedsongSlime::getInstance()
{
	if (HexusOpponentKingRedsongSlime::instance == nullptr)
	{
		HexusOpponentKingRedsongSlime::instance = new HexusOpponentKingRedsongSlime();
	}

	return HexusOpponentKingRedsongSlime::instance;
}

HexusOpponentKingRedsongSlime::HexusOpponentKingRedsongSlime() : HexusOpponentData(
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-48.0f, -96.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentKingRedsongSlime::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.53f),
	HexusOpponentData::generateDeck(25, 0.53f,
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

HexusOpponentKingRedsongSlime::~HexusOpponentKingRedsongSlime()
{
}
