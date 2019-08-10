#include "ToySoldierGoblin.h"

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

const std::string ToySoldierGoblin::MapKeyToySoldierGoblin = "toy-soldier-goblin";
HexusOpponentData* ToySoldierGoblin::HexusOpponentDataInstance = nullptr;
const std::string ToySoldierGoblin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOY_SOLDIER_GOBLIN";

ToySoldierGoblin* ToySoldierGoblin::deserialize(ValueMap& initProperties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(initProperties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Animations,
	EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Emblem,
	PlatformerCollisionType::Enemy,
	Size(112.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = ToySoldierGoblin::getHexusOpponentData();
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}

Vec2 ToySoldierGoblin::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -144.0f);
}

HexusOpponentData* ToySoldierGoblin::getHexusOpponentData()
{
	if (ToySoldierGoblin::HexusOpponentDataInstance == nullptr)
	{
		ToySoldierGoblin::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -144.0f),
			ToySoldierGoblin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.167f,
			HexusOpponentData::generateDeck(32, 0.167f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
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

	return ToySoldierGoblin::HexusOpponentDataInstance;
}