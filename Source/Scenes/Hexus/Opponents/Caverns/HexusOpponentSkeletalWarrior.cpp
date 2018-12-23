#include "HexusOpponentSkeletalWarrior.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSkeletalWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_WARRIOR";
HexusOpponentSkeletalWarrior* HexusOpponentSkeletalWarrior::instance = nullptr;

HexusOpponentSkeletalWarrior* HexusOpponentSkeletalWarrior::getInstance()
{
	if (HexusOpponentSkeletalWarrior::instance == nullptr)
	{
		HexusOpponentSkeletalWarrior::instance = new HexusOpponentSkeletalWarrior();
	}

	return HexusOpponentSkeletalWarrior::instance;
}

HexusOpponentSkeletalWarrior::HexusOpponentSkeletalWarrior() : HexusOpponentData(
	EntityResources::Enemies_SeaSharpCaverns_SkeletalWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentSkeletalWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.455f),
	HexusOpponentData::generateDeck(25, 0.455f,
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

HexusOpponentSkeletalWarrior::~HexusOpponentSkeletalWarrior()
{
}
