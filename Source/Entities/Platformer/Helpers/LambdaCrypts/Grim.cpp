#include "Grim.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/LambdaCrypts/Grim.h"

using namespace cocos2d;

const std::string Grim::MapKeyGrim = "grim";
HexusOpponentData* Grim::HexusOpponentDataInstance = nullptr;
const std::string Grim::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRIM";

Grim* Grim::deserialize(ValueMap& properties)
{
	Grim* instance = new Grim(properties);

	instance->autorelease();

	return instance;
}

Grim::Grim(ValueMap& properties) : super(properties,
	Grim::MapKeyGrim,
	nullptr,
	EntityResources::Helpers_LambdaCrypts_Grim_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Grim::getHexusOpponentData();
}

Grim::~Grim()
{
}

Vec2 Grim::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Grim::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_LambdaCrypts_Grim::create();
}

HexusOpponentData* Grim::getHexusOpponentData()
{
	if (Grim::HexusOpponentDataInstance == nullptr)
	{
		Grim::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Grim::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return Grim::HexusOpponentDataInstance;
}