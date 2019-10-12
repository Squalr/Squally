#include "Gecko.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/SeaSharpCaverns/Gecko.h"

using namespace cocos2d;

const std::string Gecko::MapKeyGecko = "gecko";
HexusOpponentData* Gecko::HexusOpponentDataInstance = nullptr;
const std::string Gecko::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GECKO";

Gecko* Gecko::deserialize(ValueMap& properties)
{
	Gecko* instance = new Gecko(properties);

	instance->autorelease();

	return instance;
}

Gecko::Gecko(ValueMap& properties) : super(properties,
	Gecko::MapKeyGecko,
	EntityResources::Helpers_SeaSharpCaverns_Gecko_Animations,
	EntityResources::Helpers_SeaSharpCaverns_Gecko_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Gecko::getHexusOpponentData();
}

Gecko::~Gecko()
{
}

Vec2 Gecko::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Gecko::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_SeaSharpCaverns_Gecko::create();
}

HexusOpponentData* Gecko::getHexusOpponentData()
{
	if (Gecko::HexusOpponentDataInstance == nullptr)
	{
		Gecko::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_SeaSharpCaverns_Gecko_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Gecko::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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

	return Gecko::HexusOpponentDataInstance;
}