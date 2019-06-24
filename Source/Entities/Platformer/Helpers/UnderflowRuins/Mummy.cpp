//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Mummy.h"

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

const std::string Mummy::MapKeyMummy = "mummy";
HexusOpponentData* Mummy::HexusOpponentDataInstance = nullptr;
const std::string Mummy::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY";

Mummy* Mummy::deserialize(ValueMap& initProperties)
{
	Mummy* instance = new Mummy(initProperties);

	instance->autorelease();

	return instance;
}

Mummy::Mummy(ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_UnderflowRuins_Mummy_Animations,
	EntityResources::Helpers_UnderflowRuins_Mummy_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Mummy::getHexusOpponentData();
}

Mummy::~Mummy()
{
}

Vec2 Mummy::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Mummy::getHexusOpponentData()
{
	if (Mummy::HexusOpponentDataInstance == nullptr)
	{
		Mummy::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_UnderflowRuins_Mummy_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Mummy::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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

	return Mummy::HexusOpponentDataInstance;
}