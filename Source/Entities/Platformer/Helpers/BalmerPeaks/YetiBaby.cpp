#include "YetiBaby.h"

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

#include "Strings/Platformer/Entities/Names/Helpers/BalmerPeaks/YetiBaby.h"

using namespace cocos2d;

const std::string YetiBaby::MapKeyYetiBaby = "yeti-baby";
HexusOpponentData* YetiBaby::HexusOpponentDataInstance = nullptr;
const std::string YetiBaby::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI_BABY";

YetiBaby* YetiBaby::deserialize(ValueMap& properties)
{
	YetiBaby* instance = new YetiBaby(properties);

	instance->autorelease();

	return instance;
}

YetiBaby::YetiBaby(ValueMap& properties) : super(properties,
	YetiBaby::MapKeyYetiBaby,
	EntityResources::Helpers_BalmerPeaks_YetiBaby_Animations,
	EntityResources::Helpers_BalmerPeaks_YetiBaby_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = YetiBaby::getHexusOpponentData();
}

YetiBaby::~YetiBaby()
{
}

Vec2 YetiBaby::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* YetiBaby::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_BalmerPeaks_YetiBaby::create();
}

HexusOpponentData* YetiBaby::getHexusOpponentData()
{
	if (YetiBaby::HexusOpponentDataInstance == nullptr)
	{
		YetiBaby::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_BalmerPeaks_YetiBaby_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			YetiBaby::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
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

	return YetiBaby::HexusOpponentDataInstance;
}