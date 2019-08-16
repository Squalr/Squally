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

DarkTiger::DarkTiger(ValueMap& properties) : PlatformerEnemy(properties,
	DarkTiger::MapKeyDarkTiger,
	EntityResources::Enemies_VoidStar_DarkTiger_Animations,
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

Vec2 DarkTiger::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DarkTiger::getHexusOpponentData()
{
	if (DarkTiger::HexusOpponentDataInstance == nullptr)
	{
		DarkTiger::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_DarkTiger_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DarkTiger::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.667f,
			HexusOpponentData::generateDeck(32, 0.667f,
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
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return DarkTiger::HexusOpponentDataInstance;
}