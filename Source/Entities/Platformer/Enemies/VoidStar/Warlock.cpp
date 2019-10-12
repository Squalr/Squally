#include "Warlock.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/VoidStar/Warlock.h"

using namespace cocos2d;

const std::string Warlock::MapKeyWarlock = "warlock";
HexusOpponentData* Warlock::HexusOpponentDataInstance = nullptr;
const std::string Warlock::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WARLOCK";

Warlock* Warlock::deserialize(ValueMap& properties)
{
	Warlock* instance = new Warlock(properties);

	instance->autorelease();

	return instance;
}

Warlock::Warlock(ValueMap& properties) : super(properties,
	Warlock::MapKeyWarlock,
	EntityResources::Enemies_VoidStar_Warlock_Animations,
	EntityResources::Enemies_VoidStar_Warlock_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Warlock::getHexusOpponentData();
}

Warlock::~Warlock()
{
}

Vec2 Warlock::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Warlock::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Warlock::create();
}

HexusOpponentData* Warlock::getHexusOpponentData()
{
	if (Warlock::HexusOpponentDataInstance == nullptr)
	{
		Warlock::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Warlock_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Warlock::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.833f,
			HexusOpponentData::generateDeck(32, 0.833f,
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

	return Warlock::HexusOpponentDataInstance;
}