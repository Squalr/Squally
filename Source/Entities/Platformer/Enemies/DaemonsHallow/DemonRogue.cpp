#include "DemonRogue.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonRogue.h"

using namespace cocos2d;

const std::string DemonRogue::MapKeyDemonRogue = "demon-rogue";
HexusOpponentData* DemonRogue::HexusOpponentDataInstance = nullptr;
const std::string DemonRogue::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_ROGUE";

DemonRogue* DemonRogue::deserialize(ValueMap& properties)
{
	DemonRogue* instance = new DemonRogue(properties);

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue(ValueMap& properties) : super(properties,
	DemonRogue::MapKeyDemonRogue,
	EntityResources::Enemies_DaemonsHallow_DemonRogue_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonRogue_Emblem,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonRogue::getHexusOpponentData();
}

DemonRogue::~DemonRogue()
{
}

Vec2 DemonRogue::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonRogue::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonRogue::create();
}

HexusOpponentData* DemonRogue::getHexusOpponentData()
{
	if (DemonRogue::HexusOpponentDataInstance == nullptr)
	{
		DemonRogue::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			DemonRogue::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.250f,
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
					
				}
			)
		);
	}

	return DemonRogue::HexusOpponentDataInstance;
}