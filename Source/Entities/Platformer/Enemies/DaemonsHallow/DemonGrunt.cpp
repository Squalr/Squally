//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

using namespace cocos2d;

const std::string DemonGrunt::MapKeyDemonGrunt = "demon-grunt";
HexusOpponentData* DemonGrunt::HexusOpponentDataInstance = nullptr;
const std::string DemonGrunt::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GRUNT";

DemonGrunt* DemonGrunt::deserialize(ValueMap& initProperties)
{
	DemonGrunt* instance = new DemonGrunt(initProperties);

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Emblem,
	PlatformerCollisionType::Enemy,
	Size(312.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = DemonGrunt::getHexusOpponentData();
}

DemonGrunt::~DemonGrunt()
{
}

Vec2 DemonGrunt::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonGrunt::getHexusOpponentData()
{
	if (DemonGrunt::HexusOpponentDataInstance == nullptr)
	{
		DemonGrunt::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonGrunt_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonGrunt::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.167f,
			HexusOpponentData::generateDeck(32, 0.167f,
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

	return DemonGrunt::HexusOpponentDataInstance;
}