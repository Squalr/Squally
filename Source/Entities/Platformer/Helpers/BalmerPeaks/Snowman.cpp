#include "Snowman.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/BalmerPeaks/Snowman.h"

using namespace cocos2d;

const std::string Snowman::MapKeySnowman = "snowman";
HexusOpponentData* Snowman::HexusOpponentDataInstance = nullptr;
const std::string Snowman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SNOWMAN";

Snowman* Snowman::deserialize(ValueMap& properties)
{
	Snowman* instance = new Snowman(properties);

	instance->autorelease();

	return instance;
}

Snowman::Snowman(ValueMap& properties) : super(properties,
	Snowman::MapKeySnowman,
	EntityResources::Helpers_BalmerPeaks_Snowman_Animations,
	EntityResources::Helpers_BalmerPeaks_Snowman_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Snowman::getHexusOpponentData();
}

Snowman::~Snowman()
{
}

Vec2 Snowman::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Snowman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_BalmerPeaks_Snowman::create();
}

HexusOpponentData* Snowman::getHexusOpponentData()
{
	if (Snowman::HexusOpponentDataInstance == nullptr)
	{
		Snowman::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Snowman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 1.000f,
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

	return Snowman::HexusOpponentDataInstance;
}