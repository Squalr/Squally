#include "HexusOpponentIrmik.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentIrmik::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_IRMIK";
HexusOpponentIrmik* HexusOpponentIrmik::instance = nullptr;

HexusOpponentIrmik* HexusOpponentIrmik::getInstance()
{
	if (HexusOpponentIrmik::instance == nullptr)
	{
		HexusOpponentIrmik::instance = new HexusOpponentIrmik();
	}

	return HexusOpponentIrmik::instance;
}

HexusOpponentIrmik::HexusOpponentIrmik() : HexusOpponentData(
	EntityResources::Npcs_LambdaPeaks_Irmik_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentIrmik::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.645f),
	HexusOpponentData::generateDeck(25, 0.645f,
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

HexusOpponentIrmik::~HexusOpponentIrmik()
{
}
