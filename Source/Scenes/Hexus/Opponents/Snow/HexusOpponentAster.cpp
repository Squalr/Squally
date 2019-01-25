#include "HexusOpponentAster.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentAster::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASTER";
HexusOpponentAster* HexusOpponentAster::instance = nullptr;

HexusOpponentAster* HexusOpponentAster::getInstance()
{
	if (HexusOpponentAster::instance == nullptr)
	{
		HexusOpponentAster::instance = new HexusOpponentAster();
	}

	return HexusOpponentAster::instance;
}

HexusOpponentAster::HexusOpponentAster() : HexusOpponentData(
	EntityResources::Npcs_BalmerPeaks_Aster_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentAster::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.625f),
	HexusOpponentData::generateDeck(25, 0.625f,
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

HexusOpponentAster::~HexusOpponentAster()
{
}
