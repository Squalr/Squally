#include "Exterminator.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Exterminator::MapKeyExterminator = "exterminator";
HexusOpponentData* Exterminator::HexusOpponentDataInstance = nullptr;
const std::string Exterminator::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXTERMINATOR";

Exterminator* Exterminator::deserialize(ValueMap& properties)
{
	Exterminator* instance = new Exterminator(properties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(ValueMap& properties) : super(properties,
	Exterminator::MapKeyExterminator,
	EntityResources::Enemies_VoidStar_Exterminator_Animations,
	EntityResources::Enemies_VoidStar_Exterminator_Emblem,
	Size(320.0f, 278.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Exterminator::getHexusOpponentData();
}

Exterminator::~Exterminator()
{
}

Vec2 Exterminator::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Exterminator::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Exterminator::create();
}

HexusOpponentData* Exterminator::getHexusOpponentData()
{
	if (Exterminator::HexusOpponentDataInstance == nullptr)
	{
		Exterminator::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Exterminator::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.917f,
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

	return Exterminator::HexusOpponentDataInstance;
}