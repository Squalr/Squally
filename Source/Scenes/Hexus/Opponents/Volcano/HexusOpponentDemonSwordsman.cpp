#include "HexusOpponentDemonSwordsman.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentDemonSwordsman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SWORDSMAN";
HexusOpponentDemonSwordsman* HexusOpponentDemonSwordsman::instance = nullptr;

HexusOpponentDemonSwordsman* HexusOpponentDemonSwordsman::getInstance()
{
	if (HexusOpponentDemonSwordsman::instance == nullptr)
	{
		HexusOpponentDemonSwordsman::instance = new HexusOpponentDemonSwordsman();
	}

	return HexusOpponentDemonSwordsman::instance;
}

HexusOpponentDemonSwordsman::HexusOpponentDemonSwordsman() : HexusOpponentData(
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-24.0f, -48.0f),
	HexusOpponentDemonSwordsman::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.745f),
	HexusOpponentData::generateDeck(25, 0.745f,
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

HexusOpponentDemonSwordsman::~HexusOpponentDemonSwordsman()
{
}
