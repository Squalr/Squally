#include "HexusOpponentJack.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentJack::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JACK";
HexusOpponentJack* HexusOpponentJack::instance = nullptr;

HexusOpponentJack* HexusOpponentJack::getInstance()
{
	if (HexusOpponentJack::instance == nullptr)
	{
		HexusOpponentJack::instance = new HexusOpponentJack();
	}

	return HexusOpponentJack::instance;
}

HexusOpponentJack::HexusOpponentJack() : HexusOpponentData(
	EntityResources::Enemies_CastleValgrind_Jack_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentJack::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.535f),
	HexusOpponentData::generateDeck(25, 0.535f,
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

HexusOpponentJack::~HexusOpponentJack()
{
}
