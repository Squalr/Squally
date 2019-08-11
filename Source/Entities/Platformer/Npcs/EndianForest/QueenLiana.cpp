#include "QueenLiana.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string QueenLiana::MapKeyQueenLiana = "queen-liana";
HexusOpponentData* QueenLiana::HexusOpponentDataInstance = nullptr;
const std::string QueenLiana::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_QUEEN_LIANA";

QueenLiana* QueenLiana::deserialize(ValueMap& initProperties)
{
	QueenLiana* instance = new QueenLiana(initProperties);

	instance->autorelease();

	return instance;
}

QueenLiana::QueenLiana(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_QueenLiana_Animations,
	EntityResources::Npcs_EndianForest_QueenLiana_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = QueenLiana::getHexusOpponentData();
}

QueenLiana::~QueenLiana()
{
}

Vec2 QueenLiana::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* QueenLiana::getHexusOpponentData()
{
	if (QueenLiana::HexusOpponentDataInstance == nullptr)
	{
		QueenLiana::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_QueenLiana_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			QueenLiana::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.098f,
			HexusOpponentData::generateDeck(32, 0.098f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),

			}),
			nullptr
		);
	}

	return QueenLiana::HexusOpponentDataInstance;
}