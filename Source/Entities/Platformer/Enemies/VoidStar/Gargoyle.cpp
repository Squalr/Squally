#include "Gargoyle.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/VoidStar/Gargoyle.h"

using namespace cocos2d;

const std::string Gargoyle::MapKeyGargoyle = "gargoyle";
HexusOpponentData* Gargoyle::HexusOpponentDataInstance = nullptr;
const std::string Gargoyle::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARGOYLE";

Gargoyle* Gargoyle::deserialize(ValueMap& properties)
{
	Gargoyle* instance = new Gargoyle(properties);

	instance->autorelease();

	return instance;
}

Gargoyle::Gargoyle(ValueMap& properties) : super(properties,
	Gargoyle::MapKeyGargoyle,
	nullptr,
	EntityResources::Enemies_VoidStar_Gargoyle_Emblem,
	Size(256.0f, 256.0f),
	0.9f,
	Vec2(-32.0f, 0.0f))
{
	this->hexusOpponentData = Gargoyle::getHexusOpponentData();
}

Gargoyle::~Gargoyle()
{
}

Vec2 Gargoyle::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Gargoyle::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Gargoyle::create();
}

HexusOpponentData* Gargoyle::getHexusOpponentData()
{
	if (Gargoyle::HexusOpponentDataInstance == nullptr)
	{
		Gargoyle::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Gargoyle::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.250f,
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

	return Gargoyle::HexusOpponentDataInstance;
}