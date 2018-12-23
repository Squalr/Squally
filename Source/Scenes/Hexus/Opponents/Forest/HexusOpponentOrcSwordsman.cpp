#include "HexusOpponentOrcSwordsman.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentOrcSwordsman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_SWORDSMAN";
HexusOpponentOrcSwordsman* HexusOpponentOrcSwordsman::instance = nullptr;

HexusOpponentOrcSwordsman* HexusOpponentOrcSwordsman::getInstance()
{
	if (HexusOpponentOrcSwordsman::instance == nullptr)
	{
		HexusOpponentOrcSwordsman::instance = new HexusOpponentOrcSwordsman();
	}

	return HexusOpponentOrcSwordsman::instance;
}

HexusOpponentOrcSwordsman::HexusOpponentOrcSwordsman() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_OrcSwordsman_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-32.0f, -40.0f),
	HexusOpponentOrcSwordsman::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.325f),
	HexusOpponentData::generateDeck(25, 0.325f,
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

HexusOpponentOrcSwordsman::~HexusOpponentOrcSwordsman()
{
}
