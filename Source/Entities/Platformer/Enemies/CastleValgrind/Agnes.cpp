#include "Agnes.h"

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

const std::string Agnes::MapKeyAgnes = "agnes";
HexusOpponentData* Agnes::HexusOpponentDataInstance = nullptr;
const std::string Agnes::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AGNES";

Agnes* Agnes::deserialize(ValueMap& properties)
{
	Agnes* instance = new Agnes(properties);

	instance->autorelease();

	return instance;
}

Agnes::Agnes(ValueMap& properties) : super(properties,
	Agnes::MapKeyAgnes,
	EntityResources::Enemies_CastleValgrind_Agnes_Animations,
	EntityResources::Enemies_CastleValgrind_Agnes_Emblem,
	Size(360.0f, 420.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Agnes::getHexusOpponentData();
}

Agnes::~Agnes()
{
}

Vec2 Agnes::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* Agnes::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Agnes::create();
}

HexusOpponentData* Agnes::getHexusOpponentData()
{
	if (Agnes::HexusOpponentDataInstance == nullptr)
	{
		Agnes::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -160.0f),
			Agnes::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				}
			)
		);
	}

	return Agnes::HexusOpponentDataInstance;
}