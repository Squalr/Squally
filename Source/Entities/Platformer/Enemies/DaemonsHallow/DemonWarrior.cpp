#include "DemonWarrior.h"

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

const std::string DemonWarrior::MapKeyDemonWarrior = "demon-warrior";
HexusOpponentData* DemonWarrior::HexusOpponentDataInstance = nullptr;
const std::string DemonWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_WARRIOR";

DemonWarrior* DemonWarrior::deserialize(ValueMap& initProperties)
{
	DemonWarrior* instance = new DemonWarrior(initProperties);

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	DemonWarrior::MapKeyDemonWarrior,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Emblem,
	Size(320.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonWarrior::getHexusOpponentData();
}

DemonWarrior::~DemonWarrior()
{
}

Vec2 DemonWarrior::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonWarrior::getHexusOpponentData()
{
	if (DemonWarrior::HexusOpponentDataInstance == nullptr)
	{
		DemonWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonWarrior_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.583f,
			HexusOpponentData::generateDeck(32, 0.583f,
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

	return DemonWarrior::HexusOpponentDataInstance;
}