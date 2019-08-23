#include "FireElemental.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/FireElemental.h"

using namespace cocos2d;

const std::string FireElemental::MapKeyFireElemental = "fire-elemental";
HexusOpponentData* FireElemental::HexusOpponentDataInstance = nullptr;
const std::string FireElemental::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FIRE_ELEMENTAL";

FireElemental* FireElemental::deserialize(ValueMap& properties)
{
	FireElemental* instance = new FireElemental(properties);

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental(ValueMap& properties) : super(properties,
	FireElemental::MapKeyFireElemental,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(64.0f, 0.0f))
{
	this->hexusOpponentData = FireElemental::getHexusOpponentData();
}

FireElemental::~FireElemental()
{
}

Vec2 FireElemental::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* FireElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_FireElemental::create();
}

HexusOpponentData* FireElemental::getHexusOpponentData()
{
	if (FireElemental::HexusOpponentDataInstance == nullptr)
	{
		FireElemental::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.0f,
			Vec2(64.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			FireElemental::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.667f,
			HexusOpponentData::generateDeck(32, 0.667f,
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

	return FireElemental::HexusOpponentDataInstance;
}