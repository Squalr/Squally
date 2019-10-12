#include "Shade.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/VoidStar/Shade.h"

using namespace cocos2d;

const std::string Shade::MapKeyShade = "shade";
HexusOpponentData* Shade::HexusOpponentDataInstance = nullptr;
const std::string Shade::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHADE";

Shade* Shade::deserialize(ValueMap& properties)
{
	Shade* instance = new Shade(properties);

	instance->autorelease();

	return instance;
}

Shade::Shade(ValueMap& properties) : super(properties,
	Shade::MapKeyShade,
	EntityResources::Enemies_VoidStar_Shade_Animations,
	EntityResources::Enemies_VoidStar_Shade_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Shade::getHexusOpponentData();
}

Shade::~Shade()
{
}

Vec2 Shade::getDialogueOffset()
{
	return Vec2(0.0f, -312.0f);
}

LocalizedString* Shade::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Shade::create();
}

HexusOpponentData* Shade::getHexusOpponentData()
{
	if (Shade::HexusOpponentDataInstance == nullptr)
	{
		Shade::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Shade_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -196.0f),
			Vec2(0.0f, -312.0f),
			Shade::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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

	return Shade::HexusOpponentDataInstance;
}