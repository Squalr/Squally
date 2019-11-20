#include "DemonDragon.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonDragon.h"

using namespace cocos2d;

const std::string DemonDragon::MapKeyDemonDragon = "demon-dragon";
HexusOpponentData* DemonDragon::HexusOpponentDataInstance = nullptr;
const std::string DemonDragon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_DRAGON";

DemonDragon* DemonDragon::deserialize(ValueMap& properties)
{
	DemonDragon* instance = new DemonDragon(properties);

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon(ValueMap& properties) : super(properties,
	DemonDragon::MapKeyDemonDragon,
	nullptr,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Emblem,
	Size(340.0f, 360.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonDragon::getHexusOpponentData();
}

DemonDragon::~DemonDragon()
{
}

Vec2 DemonDragon::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonDragon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonDragon::create();
}

HexusOpponentData* DemonDragon::getHexusOpponentData()
{
	if (DemonDragon::HexusOpponentDataInstance == nullptr)
	{
		DemonDragon::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			DemonDragon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.833f,
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

	return DemonDragon::HexusOpponentDataInstance;
}