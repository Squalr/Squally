#include "HexusOpponentSkeletalCleaver.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSkeletalCleaver::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_CLEAVER";
HexusOpponentSkeletalCleaver* HexusOpponentSkeletalCleaver::instance = nullptr;

HexusOpponentSkeletalCleaver* HexusOpponentSkeletalCleaver::getInstance()
{
	if (HexusOpponentSkeletalCleaver::instance == nullptr)
	{
		HexusOpponentSkeletalCleaver::instance = new HexusOpponentSkeletalCleaver();
	}

	return HexusOpponentSkeletalCleaver::instance;
}

HexusOpponentSkeletalCleaver::HexusOpponentSkeletalCleaver() : HexusOpponentData(
	EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentSkeletalCleaver::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.865f),
	HexusOpponentData::generateDeck(25, 0.865f,
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

HexusOpponentSkeletalCleaver::~HexusOpponentSkeletalCleaver()
{
}
