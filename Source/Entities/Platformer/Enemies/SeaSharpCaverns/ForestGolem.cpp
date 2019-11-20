#include "ForestGolem.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/SeaSharpCaverns/ForestGolem.h"

using namespace cocos2d;

const std::string ForestGolem::MapKeyForestGolem = "forest-golem";
HexusOpponentData* ForestGolem::HexusOpponentDataInstance = nullptr;
const std::string ForestGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FOREST_GOLEM";

ForestGolem* ForestGolem::deserialize(ValueMap& properties)
{
	ForestGolem* instance = new ForestGolem(properties);

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem(ValueMap& properties) : super(properties,
	ForestGolem::MapKeyForestGolem,
	EntityResources::Enemies_SeaSharpCaverns_ForestGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_ForestGolem_Emblem,
	Size(768.0f, 840.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = ForestGolem::getHexusOpponentData();
}

ForestGolem::~ForestGolem()
{
}

Vec2 ForestGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* ForestGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_ForestGolem::create();
}

HexusOpponentData* ForestGolem::getHexusOpponentData()
{
	if (ForestGolem::HexusOpponentDataInstance == nullptr)
	{
		ForestGolem::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -144.0f),
			ForestGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.417f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal14),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal10),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return ForestGolem::HexusOpponentDataInstance;
}