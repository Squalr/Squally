#include "HexusOpponentPenguinGrunt.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentPenguinGrunt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PENGUIN_GRUNT";
HexusOpponentPenguinGrunt* HexusOpponentPenguinGrunt::instance = nullptr;

HexusOpponentPenguinGrunt* HexusOpponentPenguinGrunt::getInstance()
{
	if (HexusOpponentPenguinGrunt::instance == nullptr)
	{
		HexusOpponentPenguinGrunt::instance = new HexusOpponentPenguinGrunt();
	}

	return HexusOpponentPenguinGrunt::instance;
}

HexusOpponentPenguinGrunt::HexusOpponentPenguinGrunt() : HexusOpponentData(
	EntityResources::Enemies_BalmerPeaks_PenguinGrunt_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentPenguinGrunt::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.62f),
	HexusOpponentData::generateDeck(25, 0.62f,
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

HexusOpponentPenguinGrunt::~HexusOpponentPenguinGrunt()
{
}
