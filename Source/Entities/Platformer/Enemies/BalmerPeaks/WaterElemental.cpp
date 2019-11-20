#include "WaterElemental.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/BalmerPeaks/WaterElemental.h"

using namespace cocos2d;

const std::string WaterElemental::MapKeyWaterElemental = "water-elemental";
HexusOpponentData* WaterElemental::HexusOpponentDataInstance = nullptr;
const std::string WaterElemental::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WATER_ELEMENTAL";

WaterElemental* WaterElemental::deserialize(ValueMap& properties)
{
	WaterElemental* instance = new WaterElemental(properties);

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental(ValueMap& properties) : super(properties,
	WaterElemental::MapKeyWaterElemental,
	EntityResources::Enemies_BalmerPeaks_WaterElemental_Animations,
	EntityResources::Enemies_BalmerPeaks_WaterElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = WaterElemental::getHexusOpponentData();
}

WaterElemental::~WaterElemental()
{
}

Vec2 WaterElemental::getDialogueOffset()
{
	return Vec2(-32.0f, -224.0f);
}

LocalizedString* WaterElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_WaterElemental::create();
}

HexusOpponentData* WaterElemental::getHexusOpponentData()
{
	if (WaterElemental::HexusOpponentDataInstance == nullptr)
	{
		WaterElemental::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -224.0f),
			WaterElemental::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.417f,
			{

			}),
			nullptr,
			StateOverride::create(
				// Player losses
				1,
				// Enemy losses
				1,
				// Player's turn
				true,
				// Player passed
				true,
				// Enemy passed
				true,
				// Player deck
				std::vector<CardData*>
				{
					
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return WaterElemental::HexusOpponentDataInstance;
}