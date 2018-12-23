#include "HexusOpponentExecutioner.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentExecutioner::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXECUTIONER";
HexusOpponentExecutioner* HexusOpponentExecutioner::instance = nullptr;

HexusOpponentExecutioner* HexusOpponentExecutioner::getInstance()
{
	if (HexusOpponentExecutioner::instance == nullptr)
	{
		HexusOpponentExecutioner::instance = new HexusOpponentExecutioner();
	}

	return HexusOpponentExecutioner::instance;
}

HexusOpponentExecutioner::HexusOpponentExecutioner() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Executioner_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.3f,
	Vec2(-32.0f, -160.0f),
	Vec2(-32.0f, -160.0f),
	HexusOpponentExecutioner::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.525f),
	HexusOpponentData::generateDeck(25, 0.525f,
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

HexusOpponentExecutioner::~HexusOpponentExecutioner()
{
}
