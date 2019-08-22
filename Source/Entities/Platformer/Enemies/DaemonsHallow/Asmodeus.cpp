#include "Asmodeus.h"

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

const std::string Asmodeus::MapKeyAsmodeus = "asmodeus";
HexusOpponentData* Asmodeus::HexusOpponentDataInstance = nullptr;
const std::string Asmodeus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASMODEUS";

Asmodeus* Asmodeus::deserialize(ValueMap& properties)
{
	Asmodeus* instance = new Asmodeus(properties);

	instance->autorelease();

	return instance;
}

Asmodeus::Asmodeus(ValueMap& properties) : PlatformerEnemy(properties,
	Asmodeus::MapKeyAsmodeus,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Animations,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Emblem,
	Size(480.0f, 480.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Asmodeus::getHexusOpponentData();
}

Asmodeus::~Asmodeus()
{
}

Vec2 Asmodeus::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Asmodeus::getHexusOpponentData()
{
	if (Asmodeus::HexusOpponentDataInstance == nullptr)
	{
		Asmodeus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_Asmodeus_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Asmodeus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
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

	return Asmodeus::HexusOpponentDataInstance;
}