#include "Mystic.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/LambdaCrypts/Mystic.h"

using namespace cocos2d;

const std::string Mystic::MapKeyMystic = "mystic";
HexusOpponentData* Mystic::HexusOpponentDataInstance = nullptr;
const std::string Mystic::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MYSTIC";

Mystic* Mystic::deserialize(ValueMap& properties)
{
	Mystic* instance = new Mystic(properties);

	instance->autorelease();

	return instance;
}

Mystic::Mystic(ValueMap& properties) : super(properties,
	Mystic::MapKeyMystic,
	EntityResources::Enemies_LambdaCrypts_Mystic_Animations,
	EntityResources::Enemies_LambdaCrypts_Mystic_Emblem,
	Size(420.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Mystic::getHexusOpponentData();
}

Mystic::~Mystic()
{
}

Vec2 Mystic::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Mystic::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Mystic::create();
}

HexusOpponentData* Mystic::getHexusOpponentData()
{
	if (Mystic::HexusOpponentDataInstance == nullptr)
	{
		Mystic::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Mystic::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.500f,
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

	return Mystic::HexusOpponentDataInstance;
}