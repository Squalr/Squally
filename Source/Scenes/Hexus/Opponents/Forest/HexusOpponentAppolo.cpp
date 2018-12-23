#include "HexusOpponentAppolo.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentAppolo::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APPOLO";
HexusOpponentAppolo* HexusOpponentAppolo::instance = nullptr;

HexusOpponentAppolo* HexusOpponentAppolo::getInstance()
{
	if (HexusOpponentAppolo::instance == nullptr)
	{
		HexusOpponentAppolo::instance = new HexusOpponentAppolo();
	}

	return HexusOpponentAppolo::instance;
}

HexusOpponentAppolo::HexusOpponentAppolo() : HexusOpponentData(
	EntityResources::Npcs_EndianForest_Appolo_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAppolo::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.34f),
	HexusOpponentData::generateDeck(25, 0.34f,
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

HexusOpponentAppolo::~HexusOpponentAppolo()
{
}
