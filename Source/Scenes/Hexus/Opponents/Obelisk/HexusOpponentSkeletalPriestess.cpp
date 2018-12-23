#include "HexusOpponentSkeletalPriestess.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSkeletalPriestess::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PRIESTESS";
HexusOpponentSkeletalPriestess* HexusOpponentSkeletalPriestess::instance = nullptr;

HexusOpponentSkeletalPriestess* HexusOpponentSkeletalPriestess::getInstance()
{
	if (HexusOpponentSkeletalPriestess::instance == nullptr)
	{
		HexusOpponentSkeletalPriestess::instance = new HexusOpponentSkeletalPriestess();
	}

	return HexusOpponentSkeletalPriestess::instance;
}

HexusOpponentSkeletalPriestess::HexusOpponentSkeletalPriestess() : HexusOpponentData(
	EntityResources::Enemies_LexiconCrypts_SkeletalPriestess_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentSkeletalPriestess::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.885f),
	HexusOpponentData::generateDeck(25, 0.885f,
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

HexusOpponentSkeletalPriestess::~HexusOpponentSkeletalPriestess()
{
}
