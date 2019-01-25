#include "HexusOpponentTheldar.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentTheldar::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THELDAR";
HexusOpponentTheldar* HexusOpponentTheldar::instance = nullptr;

HexusOpponentTheldar* HexusOpponentTheldar::getInstance()
{
	if (HexusOpponentTheldar::instance == nullptr)
	{
		HexusOpponentTheldar::instance = new HexusOpponentTheldar();
	}

	return HexusOpponentTheldar::instance;
}

HexusOpponentTheldar::HexusOpponentTheldar() : HexusOpponentData(
	EntityResources::Npcs_BalmerPeaks_Theldar_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentTheldar::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.695f),
	HexusOpponentData::generateDeck(25, 0.695f,
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

HexusOpponentTheldar::~HexusOpponentTheldar()
{
}
