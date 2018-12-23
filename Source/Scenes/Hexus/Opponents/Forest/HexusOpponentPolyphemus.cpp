#include "HexusOpponentPolyphemus.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentPolyphemus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POLYPHEMUS";
HexusOpponentPolyphemus* HexusOpponentPolyphemus::instance = nullptr;

HexusOpponentPolyphemus* HexusOpponentPolyphemus::getInstance()
{
	if (HexusOpponentPolyphemus::instance == nullptr)
	{
		HexusOpponentPolyphemus::instance = new HexusOpponentPolyphemus();
	}

	return HexusOpponentPolyphemus::instance;
}

HexusOpponentPolyphemus::HexusOpponentPolyphemus() : HexusOpponentData(
	EntityResources::Npcs_EndianForest_Polyphemus_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPolyphemus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.4f),
	HexusOpponentData::generateDeck(25, 0.4f,
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

HexusOpponentPolyphemus::~HexusOpponentPolyphemus()
{
}
