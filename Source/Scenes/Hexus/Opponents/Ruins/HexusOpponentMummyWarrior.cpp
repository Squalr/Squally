#include "HexusOpponentMummyWarrior.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentMummyWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_WARRIOR";
HexusOpponentMummyWarrior* HexusOpponentMummyWarrior::instance = nullptr;

HexusOpponentMummyWarrior* HexusOpponentMummyWarrior::getInstance()
{
	if (HexusOpponentMummyWarrior::instance == nullptr)
	{
		HexusOpponentMummyWarrior::instance = new HexusOpponentMummyWarrior();
	}

	return HexusOpponentMummyWarrior::instance;
}

HexusOpponentMummyWarrior::HexusOpponentMummyWarrior() : HexusOpponentData(
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentMummyWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.265f),
	HexusOpponentData::generateDeck(25, 0.265f,
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

HexusOpponentMummyWarrior::~HexusOpponentMummyWarrior()
{
}
