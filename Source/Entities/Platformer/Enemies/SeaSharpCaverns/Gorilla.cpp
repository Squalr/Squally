#include "Gorilla.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/SeaSharpCaverns/Gorilla.h"

using namespace cocos2d;

const std::string Gorilla::MapKeyGorilla = "gorilla";
HexusOpponentData* Gorilla::HexusOpponentDataInstance = nullptr;
const std::string Gorilla::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GORILLA";

Gorilla* Gorilla::deserialize(ValueMap& properties)
{
	Gorilla* instance = new Gorilla(properties);

	instance->autorelease();

	return instance;
}

Gorilla::Gorilla(ValueMap& properties) : super(properties,
	Gorilla::MapKeyGorilla,
	EntityResources::Enemies_SeaSharpCaverns_Gorilla_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Gorilla_Emblem,
	Size(512.0f, 1126.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Gorilla::getHexusOpponentData();
}

Gorilla::~Gorilla()
{
}

Vec2 Gorilla::getDialogueOffset()
{
	return Vec2(-64.0f, -144.0f);
}

LocalizedString* Gorilla::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_Gorilla::create();
}

HexusOpponentData* Gorilla::getHexusOpponentData()
{
	if (Gorilla::HexusOpponentDataInstance == nullptr)
	{
		Gorilla::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_Gorilla_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-64.0f, -144.0f),
			Gorilla::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
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

	return Gorilla::HexusOpponentDataInstance;
}