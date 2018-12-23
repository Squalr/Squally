#include "HexusOpponentYetiWarrior.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentYetiWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI_WARRIOR";
HexusOpponentYetiWarrior* HexusOpponentYetiWarrior::instance = nullptr;

HexusOpponentYetiWarrior* HexusOpponentYetiWarrior::getInstance()
{
	if (HexusOpponentYetiWarrior::instance == nullptr)
	{
		HexusOpponentYetiWarrior::instance = new HexusOpponentYetiWarrior();
	}

	return HexusOpponentYetiWarrior::instance;
}

HexusOpponentYetiWarrior::HexusOpponentYetiWarrior() : HexusOpponentData(
	EntityResources::Enemies_LambdaPeaks_YetiWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.5f,
	Vec2(-48.0f, -72.0f),
	Vec2(-24.0f, -64.0f),
	HexusOpponentYetiWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.65f),
	HexusOpponentData::generateDeck(25, 0.65f,
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

HexusOpponentYetiWarrior::~HexusOpponentYetiWarrior()
{
}
