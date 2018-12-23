#include "HexusOpponentLioness.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentLioness::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIONESS";
HexusOpponentLioness* HexusOpponentLioness::instance = nullptr;

HexusOpponentLioness* HexusOpponentLioness::getInstance()
{
	if (HexusOpponentLioness::instance == nullptr)
	{
		HexusOpponentLioness::instance = new HexusOpponentLioness();
	}

	return HexusOpponentLioness::instance;
}

HexusOpponentLioness::HexusOpponentLioness() : HexusOpponentData(
	EntityResources::Enemies_UnderflowRuins_Lioness_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentLioness::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.215f),
	HexusOpponentData::generateDeck(25, 0.215f,
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

HexusOpponentLioness::~HexusOpponentLioness()
{
}
