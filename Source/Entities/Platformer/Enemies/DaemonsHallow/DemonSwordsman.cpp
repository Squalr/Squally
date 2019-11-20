#include "DemonSwordsman.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/DaemonsHallow/DemonSwordsman.h"

using namespace cocos2d;

const std::string DemonSwordsman::MapKeyDemonSwordsman = "demon-swordsman";
HexusOpponentData* DemonSwordsman::HexusOpponentDataInstance = nullptr;
const std::string DemonSwordsman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SWORDSMAN";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap& properties)
{
	DemonSwordsman* instance = new DemonSwordsman(properties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap& properties) : super(properties,
	DemonSwordsman::MapKeyDemonSwordsman,
	nullptr,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Emblem,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonSwordsman::getHexusOpponentData();
}

DemonSwordsman::~DemonSwordsman()
{
}

Vec2 DemonSwordsman::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DemonSwordsman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonSwordsman::create();
}

HexusOpponentData* DemonSwordsman::getHexusOpponentData()
{
	if (DemonSwordsman::HexusOpponentDataInstance == nullptr)
	{
		DemonSwordsman::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			DemonSwordsman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.083f,
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

	return DemonSwordsman::HexusOpponentDataInstance;
}