#include "Professor.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/VoidStar/Professor.h"

using namespace cocos2d;

const std::string Professor::MapKeyProfessor = "professor";
HexusOpponentData* Professor::HexusOpponentDataInstance = nullptr;
const std::string Professor::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PROFESSOR";

Professor* Professor::deserialize(ValueMap& properties)
{
	Professor* instance = new Professor(properties);

	instance->autorelease();

	return instance;
}

Professor::Professor(ValueMap& properties) : super(properties,
	Professor::MapKeyProfessor,
	EntityResources::Helpers_VoidStar_Professor_Animations,
	EntityResources::Helpers_VoidStar_Professor_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Professor::getHexusOpponentData();
}

Professor::~Professor()
{
}

Vec2 Professor::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Professor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_VoidStar_Professor::create();
}

HexusOpponentData* Professor::getHexusOpponentData()
{
	if (Professor::HexusOpponentDataInstance == nullptr)
	{
		Professor::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Professor::HexusSaveKey,
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

	return Professor::HexusOpponentDataInstance;
}