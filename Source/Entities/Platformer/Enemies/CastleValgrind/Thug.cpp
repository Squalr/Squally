#include "Thug.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/CastleValgrind/Thug.h"

using namespace cocos2d;

const std::string Thug::MapKeyThug = "thug";
HexusOpponentData* Thug::HexusOpponentDataInstance = nullptr;
const std::string Thug::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THUG";

Thug* Thug::deserialize(ValueMap& properties)
{
	Thug* instance = new Thug(properties);

	instance->autorelease();

	return instance;
}

Thug::Thug(ValueMap& properties) : super(properties,
	Thug::MapKeyThug,
	EntityResources::Enemies_CastleValgrind_Thug_Animations,
	EntityResources::Enemies_CastleValgrind_Thug_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Thug::getHexusOpponentData();
}

Thug::~Thug()
{
}

Vec2 Thug::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Thug::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Thug::create();
}

HexusOpponentData* Thug::getHexusOpponentData()
{
	if (Thug::HexusOpponentDataInstance == nullptr)
	{
		Thug::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Thug_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Thug::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Thug::HexusOpponentDataInstance;
}