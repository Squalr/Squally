#include "Viking.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/BalmerPeaks/Viking.h"

using namespace cocos2d;

const std::string Viking::MapKeyViking = "viking";
HexusOpponentData* Viking::HexusOpponentDataInstance = nullptr;
const std::string Viking::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIKING";

Viking* Viking::deserialize(ValueMap& properties)
{
	Viking* instance = new Viking(properties);

	instance->autorelease();

	return instance;
}

Viking::Viking(ValueMap& properties) : super(properties,
	Viking::MapKeyViking,
	EntityResources::Enemies_BalmerPeaks_Viking_Animations,
	EntityResources::Enemies_BalmerPeaks_Viking_Emblem,
	Size(980.0f, 1200.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Viking::getHexusOpponentData();
}

Viking::~Viking()
{
}

Vec2 Viking::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* Viking::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_Viking::create();
}

HexusOpponentData* Viking::getHexusOpponentData()
{
	if (Viking::HexusOpponentDataInstance == nullptr)
	{
		Viking::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_Viking_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -144.0f),
			Viking::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
			{

			}),
			nullptr,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return Viking::HexusOpponentDataInstance;
}