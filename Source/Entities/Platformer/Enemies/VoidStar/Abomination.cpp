#include "Abomination.h"

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

const std::string Abomination::MapKeyAbomination = "abomination";
HexusOpponentData* Abomination::HexusOpponentDataInstance = nullptr;
const std::string Abomination::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ABOMINATION";

Abomination* Abomination::deserialize(ValueMap& initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Abomination_Animations,
	EntityResources::Enemies_VoidStar_Abomination_Emblem,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Abomination::getHexusOpponentData();
}

Abomination::~Abomination()
{
}

Vec2 Abomination::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Abomination::getHexusOpponentData()
{
	if (Abomination::HexusOpponentDataInstance == nullptr)
	{
		Abomination::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Abomination_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.6f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Abomination::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return Abomination::HexusOpponentDataInstance;
}