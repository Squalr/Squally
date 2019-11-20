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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/QueenLiana.h"

using namespace cocos2d;

const std::string QueenLiana::MapKeyQueenLiana = "queen-liana";
HexusOpponentData* QueenLiana::HexusOpponentDataInstance = nullptr;
const std::string QueenLiana::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_QUEEN_LIANA";

QueenLiana* QueenLiana::deserialize(ValueMap& properties)
{
	QueenLiana* instance = new QueenLiana(properties);

	instance->autorelease();

	return instance;
}

QueenLiana::QueenLiana(ValueMap& properties) : super(properties,
	QueenLiana::MapKeyQueenLiana,
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

Vec2 QueenLiana::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* QueenLiana::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_QueenLiana::create();
}

HexusOpponentData* QueenLiana::getHexusOpponentData()
{
	if (QueenLiana::HexusOpponentDataInstance == nullptr)
	{
		QueenLiana::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			QueenLiana::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
			nullptr,
			nullptr
		);
	}

	return QueenLiana::HexusOpponentDataInstance;
}