#include "HexusOpponentReaper.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentReaper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REAPER";
HexusOpponentReaper* HexusOpponentReaper::instance = nullptr;

HexusOpponentReaper* HexusOpponentReaper::getInstance()
{
	if (HexusOpponentReaper::instance == nullptr)
	{
		HexusOpponentReaper::instance = new HexusOpponentReaper();
	}

	return HexusOpponentReaper::instance;
}

HexusOpponentReaper::HexusOpponentReaper() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Reaper_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(0.0f, -224.0f),
	Vec2(-16.0f, -256.0f),
	HexusOpponentReaper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.545f),
	HexusOpponentData::generateDeck(25, 0.545f,
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

HexusOpponentReaper::~HexusOpponentReaper()
{
}
