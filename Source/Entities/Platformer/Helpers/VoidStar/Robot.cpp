#include "Robot.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/VoidStar/Robot.h"

using namespace cocos2d;

const std::string Robot::MapKeyRobot = "robot";
HexusOpponentData* Robot::HexusOpponentDataInstance = nullptr;
const std::string Robot::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROBOT";

Robot* Robot::deserialize(ValueMap& properties)
{
	Robot* instance = new Robot(properties);

	instance->autorelease();

	return instance;
}

Robot::Robot(ValueMap& properties) : super(properties,
	Robot::MapKeyRobot,
	EntityResources::Helpers_VoidStar_Robot_Animations,
	EntityResources::Helpers_VoidStar_Robot_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Robot::getHexusOpponentData();
}

Robot::~Robot()
{
}

Vec2 Robot::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Robot::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_VoidStar_Robot::create();
}

HexusOpponentData* Robot::getHexusOpponentData()
{
	if (Robot::HexusOpponentDataInstance == nullptr)
	{
		Robot::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_VoidStar_Robot_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Robot::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
			{

			}),
			{ },
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

	return Robot::HexusOpponentDataInstance;
}