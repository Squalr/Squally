#include "FireTiger.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/FireTiger.h"

using namespace cocos2d;

const std::string FireTiger::MapKeyFireTiger = "fire-tiger";
HexusOpponentData* FireTiger::HexusOpponentDataInstance = nullptr;
const std::string FireTiger::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FIRE_TIGER";

FireTiger* FireTiger::deserialize(ValueMap& properties)
{
	FireTiger* instance = new FireTiger(properties);

	instance->autorelease();

	return instance;
}

FireTiger::FireTiger(ValueMap& properties) : super(properties,
	FireTiger::MapKeyFireTiger,
	EntityResources::Enemies_DaemonsHallow_FireTiger_Animations,
	EntityResources::Enemies_DaemonsHallow_FireTiger_Emblem,
	Size(256.0f, 320.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = FireTiger::getHexusOpponentData();
}

FireTiger::~FireTiger()
{
}

Vec2 FireTiger::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* FireTiger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_FireTiger::create();
}

HexusOpponentData* FireTiger::getHexusOpponentData()
{
	if (FireTiger::HexusOpponentDataInstance == nullptr)
	{
		FireTiger::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_FireTiger_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			FireTiger::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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

	return FireTiger::HexusOpponentDataInstance;
}