#include "HexusOpponentCryogen.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentCryogen::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CRYOGEN";
HexusOpponentCryogen* HexusOpponentCryogen::instance = nullptr;

HexusOpponentCryogen* HexusOpponentCryogen::getInstance()
{
	if (HexusOpponentCryogen::instance == nullptr)
	{
		HexusOpponentCryogen::instance = new HexusOpponentCryogen();
	}

	return HexusOpponentCryogen::instance;
}

HexusOpponentCryogen::HexusOpponentCryogen() : HexusOpponentData(
	EntityResources::Enemies_BalmerPeaks_Cyrogen_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentCryogen::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.72f),
	HexusOpponentData::generateDeck(25, 0.72f,
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

HexusOpponentCryogen::~HexusOpponentCryogen()
{
}
