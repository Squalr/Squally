#include "Wraith.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/CastleValgrind/Wraith.h"

using namespace cocos2d;

const std::string Wraith::MapKeyWraith = "wraith";
HexusOpponentData* Wraith::HexusOpponentDataInstance = nullptr;
const std::string Wraith::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WRAITH";

Wraith* Wraith::deserialize(ValueMap& properties)
{
	Wraith* instance = new Wraith(properties);

	instance->autorelease();

	return instance;
}

Wraith::Wraith(ValueMap& properties) : super(properties,
	Wraith::MapKeyWraith,
	EntityResources::Enemies_CastleValgrind_Wraith_Animations,
	EntityResources::Enemies_CastleValgrind_Wraith_Emblem,
	Size(142.0f, 400.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Wraith::getHexusOpponentData();
}

Wraith::~Wraith()
{
}

Vec2 Wraith::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Wraith::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Wraith::create();
}

HexusOpponentData* Wraith::getHexusOpponentData()
{
	if (Wraith::HexusOpponentDataInstance == nullptr)
	{
		Wraith::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Wraith_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.6f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Wraith::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal14),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return Wraith::HexusOpponentDataInstance;
}