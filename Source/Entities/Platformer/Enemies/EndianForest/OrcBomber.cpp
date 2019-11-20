#include "OrcBomber.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/OrcBomber.h"

using namespace cocos2d;

const std::string OrcBomber::MapKeyOrcBomber = "orc-bomber";
HexusOpponentData* OrcBomber::HexusOpponentDataInstance = nullptr;
const std::string OrcBomber::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_BOMBER";

OrcBomber* OrcBomber::deserialize(ValueMap& properties)
{
	OrcBomber* instance = new OrcBomber(properties);

	instance->autorelease();

	return instance;
}

OrcBomber::OrcBomber(ValueMap& properties) : super(properties,
	OrcBomber::MapKeyOrcBomber,
	EntityResources::Enemies_EndianForest_OrcBomber_Animations,
	EntityResources::Enemies_EndianForest_OrcBomber_Emblem,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = OrcBomber::getHexusOpponentData();
}

OrcBomber::~OrcBomber()
{
}

Vec2 OrcBomber::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* OrcBomber::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcBomber::create();
}

HexusOpponentData* OrcBomber::getHexusOpponentData()
{
	if (OrcBomber::HexusOpponentDataInstance == nullptr)
	{
		OrcBomber::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			OrcBomber::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.769f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Mov),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
				}
			)
		);
	}

	return OrcBomber::HexusOpponentDataInstance;
}