#include "Hunter.h"

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

const std::string Hunter::MapKeyHunter = "hunter";
HexusOpponentData* Hunter::HexusOpponentDataInstance = nullptr;
const std::string Hunter::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HUNTER";

Hunter* Hunter::deserialize(ValueMap& initProperties)
{
	Hunter* instance = new Hunter(initProperties);

	instance->autorelease();

	return instance;
}

Hunter::Hunter(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	Hunter::MapKeyHunter,
	EntityResources::Enemies_LambdaCrypts_Hunter_Animations,
	EntityResources::Enemies_LambdaCrypts_Hunter_Emblem,
	Size(112.0f, 596.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Hunter::getHexusOpponentData();
}

Hunter::~Hunter()
{
}

Vec2 Hunter::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Hunter::getHexusOpponentData()
{
	if (Hunter::HexusOpponentDataInstance == nullptr)
	{
		Hunter::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_Hunter_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Hunter::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.417f,
			HexusOpponentData::generateDeck(32, 0.417f,
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

	return Hunter::HexusOpponentDataInstance;
}