#include "OrcGrunt.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/OrcGrunt.h"

using namespace cocos2d;

const std::string OrcGrunt::MapKeyOrcGrunt = "orc-grunt";
HexusOpponentData* OrcGrunt::HexusOpponentDataInstance = nullptr;
const std::string OrcGrunt::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_GRUNT";

OrcGrunt* OrcGrunt::deserialize(ValueMap& properties)
{
	OrcGrunt* instance = new OrcGrunt(properties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(ValueMap& properties) : super(properties,
	OrcGrunt::MapKeyOrcGrunt,
	EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
	EntityResources::Enemies_EndianForest_OrcGrunt_Emblem,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = OrcGrunt::getHexusOpponentData();

	this->dropTable.push_back(this->createDrop(HealthPotion::SaveKeyHealthPotion, 0.5f));
	this->dropTable.push_back(this->createDrop(ManaPotion::SaveKeyManaPotion, 0.5f));
	this->iouTable = std::make_tuple(1, 2);
}

OrcGrunt::~OrcGrunt()
{
}

Vec2 OrcGrunt::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* OrcGrunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcGrunt::create();
}

HexusOpponentData* OrcGrunt::getHexusOpponentData()
{
	if (OrcGrunt::HexusOpponentDataInstance == nullptr)
	{
		OrcGrunt::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			OrcGrunt::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.077f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
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

	return OrcGrunt::HexusOpponentDataInstance;
}
