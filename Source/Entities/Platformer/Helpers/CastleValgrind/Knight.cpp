#include "Knight.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/CastleValgrind/Knight.h"

using namespace cocos2d;

const std::string Knight::MapKeyKnight = "knight";
HexusOpponentData* Knight::HexusOpponentDataInstance = nullptr;
const std::string Knight::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KNIGHT";

Knight* Knight::deserialize(ValueMap& properties)
{
	Knight* instance = new Knight(properties);

	instance->autorelease();

	return instance;
}

Knight::Knight(ValueMap& properties) : super(properties,
	Knight::MapKeyKnight,
	EntityResources::Helpers_CastleValgrind_Knight_Animations,
	EntityResources::Helpers_CastleValgrind_Knight_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Knight::getHexusOpponentData();
}

Knight::~Knight()
{
}

Vec2 Knight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Knight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Knight::create();
}

HexusOpponentData* Knight::getHexusOpponentData()
{
	if (Knight::HexusOpponentDataInstance == nullptr)
	{
		Knight::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Knight::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
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

	return Knight::HexusOpponentDataInstance;
}