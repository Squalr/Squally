#include "GoblinShaman.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/GoblinShaman.h"

using namespace cocos2d;

const std::string GoblinShaman::MapKeyGoblinShaman = "goblin-shaman";
HexusOpponentData* GoblinShaman::HexusOpponentDataInstance = nullptr;
const std::string GoblinShaman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_SHAMAN";

GoblinShaman* GoblinShaman::deserialize(ValueMap& properties)
{
	GoblinShaman* instance = new GoblinShaman(properties);

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman(ValueMap& properties) : super(properties,
	GoblinShaman::MapKeyGoblinShaman,
	EntityResources::Enemies_EndianForest_GoblinShaman_Animations,
	EntityResources::Enemies_EndianForest_GoblinShaman_Emblem,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = GoblinShaman::getHexusOpponentData();
}

GoblinShaman::~GoblinShaman()
{
}

Vec2 GoblinShaman::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* GoblinShaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_GoblinShaman::create();
}

HexusOpponentData* GoblinShaman::getHexusOpponentData()
{
	if (GoblinShaman::HexusOpponentDataInstance == nullptr)
	{
		GoblinShaman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_GoblinShaman_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			GoblinShaman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.538f,
			HexusOpponentData::generateDeck(32, 0.538f,
			{

			}),
			{ },
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return GoblinShaman::HexusOpponentDataInstance;
}