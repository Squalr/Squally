#include "HexusOpponentEnt.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentEnt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ENT";
HexusOpponentEnt* HexusOpponentEnt::instance = nullptr;

HexusOpponentEnt* HexusOpponentEnt::getInstance()
{
	if (HexusOpponentEnt::instance == nullptr)
	{
		HexusOpponentEnt::instance = new HexusOpponentEnt();
	}

	return HexusOpponentEnt::instance;
}

HexusOpponentEnt::HexusOpponentEnt() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_Ent_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	0.85f,
	Vec2(-144.0f, -128.0f),
	Vec2(-156.0f, -212.0f),
	HexusOpponentEnt::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.375f),
	HexusOpponentData::generateDeck(25, 0.375f,
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

HexusOpponentEnt::~HexusOpponentEnt()
{
}
