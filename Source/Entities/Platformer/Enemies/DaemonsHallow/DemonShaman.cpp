#include "DemonShaman.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonShaman.h"

using namespace cocos2d;

const std::string DemonShaman::MapKeyDemonShaman = "demon-shaman";
HexusOpponentData* DemonShaman::HexusOpponentDataInstance = nullptr;
const std::string DemonShaman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SHAMAN";

DemonShaman* DemonShaman::deserialize(ValueMap& properties)
{
	DemonShaman* instance = new DemonShaman(properties);

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman(ValueMap& properties) : super(properties,
	DemonShaman::MapKeyDemonShaman,
	EntityResources::Enemies_DaemonsHallow_DemonShaman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonShaman_Emblem,
	Size(212.0f, 280.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonShaman::getHexusOpponentData();
}

DemonShaman::~DemonShaman()
{
}

Vec2 DemonShaman::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonShaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonShaman::create();
}

HexusOpponentData* DemonShaman::getHexusOpponentData()
{
	if (DemonShaman::HexusOpponentDataInstance == nullptr)
	{
		DemonShaman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonShaman_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonShaman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.417f,
			HexusOpponentData::generateDeck(32, 0.417f,
			{

			}),
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
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return DemonShaman::HexusOpponentDataInstance;
}