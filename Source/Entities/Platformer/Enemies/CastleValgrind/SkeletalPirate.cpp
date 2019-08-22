#include "SkeletalPirate.h"

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

const std::string SkeletalPirate::MapKeySkeletalPirate = "skeletal-pirate";
HexusOpponentData* SkeletalPirate::HexusOpponentDataInstance = nullptr;
const std::string SkeletalPirate::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PIRATE";

SkeletalPirate* SkeletalPirate::deserialize(ValueMap& properties)
{
	SkeletalPirate* instance = new SkeletalPirate(properties);

	instance->autorelease();

	return instance;
}

SkeletalPirate::SkeletalPirate(ValueMap& properties) : PlatformerEnemy(properties,
	SkeletalPirate::MapKeySkeletalPirate,
	EntityResources::Enemies_CastleValgrind_SkeletalPirate_Animations,
	EntityResources::Enemies_CastleValgrind_SkeletalPirate_Emblem,
	Size(112.0f, 820.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = SkeletalPirate::getHexusOpponentData();
}

SkeletalPirate::~SkeletalPirate()
{
}

Vec2 SkeletalPirate::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* SkeletalPirate::getHexusOpponentData()
{
	if (SkeletalPirate::HexusOpponentDataInstance == nullptr)
	{
		SkeletalPirate::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_SkeletalPirate_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			SkeletalPirate::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.333f,
			HexusOpponentData::generateDeck(32, 0.333f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return SkeletalPirate::HexusOpponentDataInstance;
}