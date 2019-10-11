#include "DemonGhost.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonGhost.h"

using namespace cocos2d;

const std::string DemonGhost::MapKeyDemonGhost = "demon-ghost";
HexusOpponentData* DemonGhost::HexusOpponentDataInstance = nullptr;
const std::string DemonGhost::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GHOST";

DemonGhost* DemonGhost::deserialize(ValueMap& properties)
{
	DemonGhost* instance = new DemonGhost(properties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(ValueMap& properties) : super(properties,
	DemonGhost::MapKeyDemonGhost,
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Emblem,
	Size(256.0f, 320.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonGhost::getHexusOpponentData();
}

DemonGhost::~DemonGhost()
{
}

Vec2 DemonGhost::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonGhost::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonGhost::create();
}

HexusOpponentData* DemonGhost::getHexusOpponentData()
{
	if (DemonGhost::HexusOpponentDataInstance == nullptr)
	{
		DemonGhost::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonGhost::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.500f,
			HexusOpponentData::generateDeck(32, 0.500f,
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

	return DemonGhost::HexusOpponentDataInstance;
}