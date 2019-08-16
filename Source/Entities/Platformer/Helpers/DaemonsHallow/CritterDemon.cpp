#include "CritterDemon.h"

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

const std::string CritterDemon::MapKeyCritterDemon = "critter-demon";
HexusOpponentData* CritterDemon::HexusOpponentDataInstance = nullptr;
const std::string CritterDemon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CRITTER_DEMON";

CritterDemon* CritterDemon::deserialize(ValueMap& properties)
{
	CritterDemon* instance = new CritterDemon(properties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(ValueMap& properties) : PlatformerEntity(properties,
	CritterDemon::MapKeyCritterDemon,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Animations,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Emblem,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = CritterDemon::getHexusOpponentData();
}

CritterDemon::~CritterDemon()
{
}

Vec2 CritterDemon::getAvatarFrameOffset()
{
	return Vec2(-48.0f, -112.0f);
}

HexusOpponentData* CritterDemon::getHexusOpponentData()
{
	if (CritterDemon::HexusOpponentDataInstance == nullptr)
	{
		CritterDemon::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_DaemonsHallow_CritterDemon_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(-32.0f, -128.0f),
			Vec2(-48.0f, -112.0f),
			CritterDemon::HexusSaveKey,
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

	return CritterDemon::HexusOpponentDataInstance;
}