#include "HexusOpponentHorus.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentHorus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HORUS";
HexusOpponentHorus* HexusOpponentHorus::instance = nullptr;

HexusOpponentHorus* HexusOpponentHorus::getInstance()
{
	if (HexusOpponentHorus::instance == nullptr)
	{
		HexusOpponentHorus::instance = new HexusOpponentHorus();
	}

	return HexusOpponentHorus::instance;
}

HexusOpponentHorus::HexusOpponentHorus() : HexusOpponentData(
	EntityResources::Npcs_UnderflowRuins_Horus_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentHorus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.2f),
	HexusOpponentData::generateDeck(25, 0.2f,
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

HexusOpponentHorus::~HexusOpponentHorus()
{
}
