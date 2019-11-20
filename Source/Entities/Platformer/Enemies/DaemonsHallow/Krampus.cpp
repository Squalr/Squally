#include "Krampus.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/Krampus.h"

using namespace cocos2d;

const std::string Krampus::MapKeyKrampus = "krampus";
HexusOpponentData* Krampus::HexusOpponentDataInstance = nullptr;
const std::string Krampus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KRAMPUS";

Krampus* Krampus::deserialize(ValueMap& properties)
{
	Krampus* instance = new Krampus(properties);

	instance->autorelease();

	return instance;
}

Krampus::Krampus(ValueMap& properties) : super(properties,
	Krampus::MapKeyKrampus,
	EntityResources::Enemies_DaemonsHallow_Krampus_Animations,
	EntityResources::Enemies_DaemonsHallow_Krampus_Emblem,
	Size(396.0f, 412.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Krampus::getHexusOpponentData();
}

Krampus::~Krampus()
{
}

Vec2 Krampus::getDialogueOffset()
{
	return Vec2(-48.0f, -232.0f);
}

LocalizedString* Krampus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_Krampus::create();
}

HexusOpponentData* Krampus::getHexusOpponentData()
{
	if (Krampus::HexusOpponentDataInstance == nullptr)
	{
		Krampus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-48.0f, -232.0f),
			Krampus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.917f,
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

	return Krampus::HexusOpponentDataInstance;
}