#include "HexusOpponentGoblinWarriorPig.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentGoblinWarriorPig::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_WARRIOR_PIG";
HexusOpponentGoblinWarriorPig* HexusOpponentGoblinWarriorPig::instance = nullptr;

HexusOpponentGoblinWarriorPig* HexusOpponentGoblinWarriorPig::getInstance()
{
	if (HexusOpponentGoblinWarriorPig::instance == nullptr)
	{
		HexusOpponentGoblinWarriorPig::instance = new HexusOpponentGoblinWarriorPig();
	}

	return HexusOpponentGoblinWarriorPig::instance;
}

HexusOpponentGoblinWarriorPig::HexusOpponentGoblinWarriorPig() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -32.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGoblinWarriorPig::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.105f),
	HexusOpponentData::generateDeck(25, 0.105f,
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentGoblinWarriorPig::~HexusOpponentGoblinWarriorPig()
{
}
