#include "HexusOpponentPrincessMittens.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentPrincessMittens::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MITTENS";
HexusOpponentPrincessMittens* HexusOpponentPrincessMittens::instance = nullptr;

HexusOpponentPrincessMittens* HexusOpponentPrincessMittens::getInstance()
{
	if (HexusOpponentPrincessMittens::instance == nullptr)
	{
		HexusOpponentPrincessMittens::instance = new HexusOpponentPrincessMittens();
	}

	return HexusOpponentPrincessMittens::instance;
}

HexusOpponentPrincessMittens::HexusOpponentPrincessMittens() : HexusOpponentData(
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentPrincessMittens::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.39f),
	HexusOpponentData::generateDeck(25, 0.39f,
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

HexusOpponentPrincessMittens::~HexusOpponentPrincessMittens()
{
}
