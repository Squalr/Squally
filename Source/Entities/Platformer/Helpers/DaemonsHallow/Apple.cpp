#include "Apple.h"

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

const std::string Apple::MapKeyApple = "apple";
HexusOpponentData* Apple::HexusOpponentDataInstance = nullptr;
const std::string Apple::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APPLE";

Apple* Apple::deserialize(ValueMap& initProperties)
{
	Apple* instance = new Apple(initProperties);

	instance->autorelease();

	return instance;
}

Apple::Apple(ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_DaemonsHallow_Apple_Animations,
	EntityResources::Helpers_DaemonsHallow_Apple_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Apple::getHexusOpponentData();
}

Apple::~Apple()
{
}

Vec2 Apple::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Apple::getHexusOpponentData()
{
	if (Apple::HexusOpponentDataInstance == nullptr)
	{
		Apple::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_DaemonsHallow_Apple_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Apple::HexusSaveKey,
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

	return Apple::HexusOpponentDataInstance;
}