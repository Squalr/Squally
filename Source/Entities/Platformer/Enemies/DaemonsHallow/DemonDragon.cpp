#include "DemonDragon.h"

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

const std::string DemonDragon::MapKeyDemonDragon = "demon-dragon";
HexusOpponentData* DemonDragon::HexusOpponentDataInstance = nullptr;
const std::string DemonDragon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_DRAGON";

DemonDragon* DemonDragon::deserialize(ValueMap& initProperties)
{
	DemonDragon* instance = new DemonDragon(initProperties);

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Emblem,
	PlatformerCollisionType::Enemy,
	Size(340.0f, 360.0f),
	0.85f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = DemonDragon::getHexusOpponentData();
}

DemonDragon::~DemonDragon()
{
}

Vec2 DemonDragon::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonDragon::getHexusOpponentData()
{
	if (DemonDragon::HexusOpponentDataInstance == nullptr)
	{
		DemonDragon::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonDragon_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonDragon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.833f,
			HexusOpponentData::generateDeck(32, 0.833f,
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

	return DemonDragon::HexusOpponentDataInstance;
}