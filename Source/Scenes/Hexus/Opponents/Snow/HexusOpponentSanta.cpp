#include "HexusOpponentSanta.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSanta::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SANTA";
HexusOpponentSanta* HexusOpponentSanta::instance = nullptr;

HexusOpponentSanta* HexusOpponentSanta::getInstance()
{
	if (HexusOpponentSanta::instance == nullptr)
	{
		HexusOpponentSanta::instance = new HexusOpponentSanta();
	}

	return HexusOpponentSanta::instance;
}

HexusOpponentSanta::HexusOpponentSanta() : HexusOpponentData(
	EntityResources::Enemies_LambdaPeaks_Santa_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentSanta::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.715f),
	HexusOpponentData::generateDeck(25, 0.715f,
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

HexusOpponentSanta::~HexusOpponentSanta()
{
}
