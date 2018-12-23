#include "HexusOpponentTyracius.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentTyracius::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TYRACIUS";
HexusOpponentTyracius* HexusOpponentTyracius::instance = nullptr;

HexusOpponentTyracius* HexusOpponentTyracius::getInstance()
{
	if (HexusOpponentTyracius::instance == nullptr)
	{
		HexusOpponentTyracius::instance = new HexusOpponentTyracius();
	}

	return HexusOpponentTyracius::instance;
}

HexusOpponentTyracius::HexusOpponentTyracius() : HexusOpponentData(
	EntityResources::Npcs_CastleValgrind_Tyracius_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentTyracius::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.54f),
	HexusOpponentData::generateDeck(25, 0.54f,
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

HexusOpponentTyracius::~HexusOpponentTyracius()
{
}
