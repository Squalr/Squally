#include "Princess.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/CastleValgrind/Princess.h"

using namespace cocos2d;

const std::string Princess::MapKeyPrincess = "princess";
HexusOpponentData* Princess::HexusOpponentDataInstance = nullptr;
const std::string Princess::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS";

Princess* Princess::deserialize(ValueMap& properties)
{
	Princess* instance = new Princess(properties);

	instance->autorelease();

	return instance;
}

Princess::Princess(ValueMap& properties) : super(properties,
	Princess::MapKeyPrincess,
	EntityResources::Helpers_CastleValgrind_Princess_Animations,
	EntityResources::Helpers_CastleValgrind_Princess_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Princess::getHexusOpponentData();
}

Princess::~Princess()
{
}

Vec2 Princess::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Princess::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Princess::create();
}

HexusOpponentData* Princess::getHexusOpponentData()
{
	if (Princess::HexusOpponentDataInstance == nullptr)
	{
		Princess::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_CastleValgrind_Princess_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Princess::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
			{

			}),
			nullptr,
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

	return Princess::HexusOpponentDataInstance;
}