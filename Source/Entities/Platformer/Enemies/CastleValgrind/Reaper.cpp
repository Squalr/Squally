//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Reaper.h"

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

const std::string Reaper::MapKeyReaper = "reaper";
HexusOpponentData* Reaper::HexusOpponentDataInstance = nullptr;
const std::string Reaper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REAPER";

Reaper* Reaper::deserialize(ValueMap& initProperties)
{
	Reaper* instance = new Reaper(initProperties);

	instance->autorelease();

	return instance;
}

Reaper::Reaper(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Reaper_Animations,
	EntityResources::Enemies_CastleValgrind_Reaper_Emblem,
	PlatformerCollisionType::Enemy,
	Size(196.0f, 512.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Reaper::getHexusOpponentData();
}

Reaper::~Reaper()
{
}

Vec2 Reaper::getAvatarFrameOffset()
{
	return Vec2(-16.0f, -288.0f);
}

HexusOpponentData* Reaper::getHexusOpponentData()
{
	if (Reaper::HexusOpponentDataInstance == nullptr)
	{
		Reaper::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Reaper_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -160.0f),
			Vec2(-16.0f, -288.0f),
			Reaper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.583f,
			HexusOpponentData::generateDeck(32, 0.583f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Steal),
CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Reaper::HexusOpponentDataInstance;
}