#include "Ghost.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ghost::MapKeyGhost = "ghost";
HexusOpponentData* Ghost::HexusOpponentDataInstance = nullptr;
const std::string Ghost::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GHOST";

Ghost* Ghost::deserialize(ValueMap& properties)
{
	Ghost* instance = new Ghost(properties);

	instance->autorelease();

	return instance;
}

Ghost::Ghost(ValueMap& properties) : super(properties,
	Ghost::MapKeyGhost,
	EntityResources::Helpers_LambdaCrypts_Ghost_Animations,
	EntityResources::Helpers_LambdaCrypts_Ghost_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ghost::getHexusOpponentData();
}

Ghost::~Ghost()
{
}

Vec2 Ghost::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ghost::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_LambdaCrypts_Ghost::create();
}

HexusOpponentData* Ghost::getHexusOpponentData()
{
	if (Ghost::HexusOpponentDataInstance == nullptr)
	{
		Ghost::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Ghost::HexusSaveKey,
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

	return Ghost::HexusOpponentDataInstance;
}