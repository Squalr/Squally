#include "HexusOpponentXenon.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentXenon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_XENON";
HexusOpponentXenon* HexusOpponentXenon::instance = nullptr;

HexusOpponentXenon* HexusOpponentXenon::getInstance()
{
	if (HexusOpponentXenon::instance == nullptr)
	{
		HexusOpponentXenon::instance = new HexusOpponentXenon();
	}

	return HexusOpponentXenon::instance;
}

HexusOpponentXenon::HexusOpponentXenon() : HexusOpponentData(
	EntityResources::Npcs_VoidStar_Xenon_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentXenon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.98f),
	HexusOpponentData::generateDeck(25, 0.98f,
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

HexusOpponentXenon::~HexusOpponentXenon()
{
}
