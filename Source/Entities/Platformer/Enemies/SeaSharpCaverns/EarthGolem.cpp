#include "EarthGolem.h"

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

const std::string EarthGolem::MapKeyEarthGolem = "earth-golem";
HexusOpponentData* EarthGolem::HexusOpponentDataInstance = nullptr;
const std::string EarthGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EARTH_GOLEM";

EarthGolem* EarthGolem::deserialize(ValueMap& initProperties)
{
	EarthGolem* instance = new EarthGolem(initProperties);

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_EarthGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_EarthGolem_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = EarthGolem::getHexusOpponentData();
}

EarthGolem::~EarthGolem()
{
}

Vec2 EarthGolem::getAvatarFrameOffset()
{
	return Vec2(-48.0f, -144.0f);
}

HexusOpponentData* EarthGolem::getHexusOpponentData()
{
	if (EarthGolem::HexusOpponentDataInstance == nullptr)
	{
		EarthGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_EarthGolem_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-48.0f, -144.0f),
			EarthGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
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

	return EarthGolem::HexusOpponentDataInstance;
}