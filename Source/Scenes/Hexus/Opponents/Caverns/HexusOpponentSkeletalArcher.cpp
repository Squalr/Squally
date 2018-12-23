#include "HexusOpponentSkeletalArcher.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSkeletalArcher::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_ARCHER";
HexusOpponentSkeletalArcher* HexusOpponentSkeletalArcher::instance = nullptr;

HexusOpponentSkeletalArcher* HexusOpponentSkeletalArcher::getInstance()
{
	if (HexusOpponentSkeletalArcher::instance == nullptr)
	{
		HexusOpponentSkeletalArcher::instance = new HexusOpponentSkeletalArcher();
	}

	return HexusOpponentSkeletalArcher::instance;
}

HexusOpponentSkeletalArcher::HexusOpponentSkeletalArcher() : HexusOpponentData(
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentSkeletalArcher::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.445f),
	HexusOpponentData::generateDeck(25, 0.445f,
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

HexusOpponentSkeletalArcher::~HexusOpponentSkeletalArcher()
{
}
