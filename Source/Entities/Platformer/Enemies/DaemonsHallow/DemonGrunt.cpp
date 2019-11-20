#include "DemonGrunt.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonGrunt.h"

using namespace cocos2d;

const std::string DemonGrunt::MapKeyDemonGrunt = "demon-grunt";
HexusOpponentData* DemonGrunt::HexusOpponentDataInstance = nullptr;
const std::string DemonGrunt::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GRUNT";

DemonGrunt* DemonGrunt::deserialize(ValueMap& properties)
{
	DemonGrunt* instance = new DemonGrunt(properties);

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt(ValueMap& properties) : super(properties,
	DemonGrunt::MapKeyDemonGrunt,
	nullptr,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Emblem,
	Size(312.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonGrunt::getHexusOpponentData();
}

DemonGrunt::~DemonGrunt()
{
}

Vec2 DemonGrunt::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonGrunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonGrunt::create();
}

HexusOpponentData* DemonGrunt::getHexusOpponentData()
{
	if (DemonGrunt::HexusOpponentDataInstance == nullptr)
	{
		DemonGrunt::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			DemonGrunt::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.167f,
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

	return DemonGrunt::HexusOpponentDataInstance;
}