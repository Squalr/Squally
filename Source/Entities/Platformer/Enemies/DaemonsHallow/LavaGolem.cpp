#include "LavaGolem.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/LavaGolem.h"

using namespace cocos2d;

const std::string LavaGolem::MapKeyLavaGolem = "lava-golem";
HexusOpponentData* LavaGolem::HexusOpponentDataInstance = nullptr;
const std::string LavaGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LAVA_GOLEM";

LavaGolem* LavaGolem::deserialize(ValueMap& properties)
{
	LavaGolem* instance = new LavaGolem(properties);

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem(ValueMap& properties) : super(properties,
	LavaGolem::MapKeyLavaGolem,
	EntityResources::Enemies_DaemonsHallow_LavaGolem_Animations,
	EntityResources::Enemies_DaemonsHallow_LavaGolem_Emblem,
	Size(980.0f, 1200.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = LavaGolem::getHexusOpponentData();
}

LavaGolem::~LavaGolem()
{
}

Vec2 LavaGolem::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* LavaGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_LavaGolem::create();
}

HexusOpponentData* LavaGolem::getHexusOpponentData()
{
	if (LavaGolem::HexusOpponentDataInstance == nullptr)
	{
		LavaGolem::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			LavaGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.333f,
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

	return LavaGolem::HexusOpponentDataInstance;
}