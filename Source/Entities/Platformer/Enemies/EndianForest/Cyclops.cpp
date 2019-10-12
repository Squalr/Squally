#include "Cyclops.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/Cyclops.h"

using namespace cocos2d;

const std::string Cyclops::MapKeyCyclops = "cyclops";
HexusOpponentData* Cyclops::HexusOpponentDataInstance = nullptr;
const std::string Cyclops::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CYCLOPS";

Cyclops* Cyclops::deserialize(ValueMap& properties)
{
	Cyclops* instance = new Cyclops(properties);

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops(ValueMap& properties) : super(properties,
	Cyclops::MapKeyCyclops,
	EntityResources::Enemies_EndianForest_Cyclops_Animations,
	EntityResources::Enemies_EndianForest_Cyclops_Emblem,
	Size(296.0f, 256.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cyclops::getHexusOpponentData();
}

Cyclops::~Cyclops()
{
}

Vec2 Cyclops::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* Cyclops::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Cyclops::create();
}

HexusOpponentData* Cyclops::getHexusOpponentData()
{
	if (Cyclops::HexusOpponentDataInstance == nullptr)
	{
		Cyclops::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Cyclops_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -196.0f),
			Cyclops::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.462f,
			HexusOpponentData::generateDeck(32, 0.462f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
				}
			)
		);
	}

	return Cyclops::HexusOpponentDataInstance;
}