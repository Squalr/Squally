#include "GoblinGruntBoar.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/GoblinGruntBoar.h"

using namespace cocos2d;

const std::string GoblinGruntBoar::MapKeyGoblinGruntBoar = "goblin-grunt-boar";
HexusOpponentData* GoblinGruntBoar::HexusOpponentDataInstance = nullptr;
const std::string GoblinGruntBoar::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_GRUNT_BOAR";

GoblinGruntBoar* GoblinGruntBoar::deserialize(ValueMap& properties)
{
	GoblinGruntBoar* instance = new GoblinGruntBoar(properties);

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar(ValueMap& properties) : super(properties,
	GoblinGruntBoar::MapKeyGoblinGruntBoar,
	EntityResources::Enemies_EndianForest_GoblinGruntBoar_Animations,
	EntityResources::Enemies_EndianForest_GoblinGruntBoar_Emblem,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = GoblinGruntBoar::getHexusOpponentData();
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}

Vec2 GoblinGruntBoar::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* GoblinGruntBoar::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_GoblinGruntBoar::create();
}

HexusOpponentData* GoblinGruntBoar::getHexusOpponentData()
{
	if (GoblinGruntBoar::HexusOpponentDataInstance == nullptr)
	{
		GoblinGruntBoar::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_GoblinGruntBoar_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -128.0f),
			GoblinGruntBoar::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.308f,
			HexusOpponentData::generateDeck(32, 0.308f,
			{

			}),
			nullptr,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return GoblinGruntBoar::HexusOpponentDataInstance;
}