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

DemonRogue::DemonRogue(ValueMap& properties) : PlatformerEnemy(properties,
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

Vec2 DemonRogue::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonRogue::getHexusOpponentData()
{
	if (DemonRogue::HexusOpponentDataInstance == nullptr)
	{
		DemonRogue::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonRogue_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonRogue::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
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

	return DemonRogue::HexusOpponentDataInstance;
}