#include "DarkTiger.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/VoidStar/DarkTiger.h"

using namespace cocos2d;

const std::string DarkTiger::MapKeyDarkTiger = "dark-tiger";
HexusOpponentData* DarkTiger::HexusOpponentDataInstance = nullptr;
const std::string DarkTiger::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DARK_TIGER";

DarkTiger* DarkTiger::deserialize(ValueMap& properties)
{
	DarkTiger* instance = new DarkTiger(properties);

	instance->autorelease();

	return instance;
}

DarkTiger::DarkTiger(ValueMap& properties) : super(properties,
	DarkTiger::MapKeyDarkTiger,
	nullptr,
	EntityResources::Enemies_VoidStar_DarkTiger_Emblem,
	Size(256.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DarkTiger::getHexusOpponentData();
}

DarkTiger::~DarkTiger()
{
}

Vec2 DarkTiger::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* DarkTiger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_DarkTiger::create();
}

HexusOpponentData* DarkTiger::getHexusOpponentData()
{
	if (DarkTiger::HexusOpponentDataInstance == nullptr)
	{
		DarkTiger::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			DarkTiger::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.667f,
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

	return DarkTiger::HexusOpponentDataInstance;
}