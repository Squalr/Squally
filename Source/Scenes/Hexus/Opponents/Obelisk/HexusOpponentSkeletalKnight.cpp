#include "HexusOpponentSkeletalKnight.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSkeletalKnight::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_KNIGHT";
HexusOpponentSkeletalKnight* HexusOpponentSkeletalKnight::instance = nullptr;

HexusOpponentSkeletalKnight* HexusOpponentSkeletalKnight::getInstance()
{
	if (HexusOpponentSkeletalKnight::instance == nullptr)
	{
		HexusOpponentSkeletalKnight::instance = new HexusOpponentSkeletalKnight();
	}

	return HexusOpponentSkeletalKnight::instance;
}

HexusOpponentSkeletalKnight::HexusOpponentSkeletalKnight() : HexusOpponentData(
	EntityResources::Enemies_LambdaCrypts_SkeletalKnight_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentSkeletalKnight::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.875f),
	HexusOpponentData::generateDeck(25, 0.875f,
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

HexusOpponentSkeletalKnight::~HexusOpponentSkeletalKnight()
{
}
