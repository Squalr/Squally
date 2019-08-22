#include "TigerMan.h"

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

const std::string TigerMan::MapKeyTigerMan = "tiger-man";
HexusOpponentData* TigerMan::HexusOpponentDataInstance = nullptr;
const std::string TigerMan::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIGER_MAN";

TigerMan* TigerMan::deserialize(ValueMap& properties)
{
	TigerMan* instance = new TigerMan(properties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap& properties) : PlatformerEnemy(properties,
	TigerMan::MapKeyTigerMan,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Animations,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Emblem,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = TigerMan::getHexusOpponentData();
}

TigerMan::~TigerMan()
{
}

Vec2 TigerMan::getDialogueOffset()
{
	return Vec2(-16.0f, -212.0f);
}

HexusOpponentData* TigerMan::getHexusOpponentData()
{
	if (TigerMan::HexusOpponentDataInstance == nullptr)
	{
		TigerMan::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_TigerMan_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-16.0f, -212.0f),
			TigerMan::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return TigerMan::HexusOpponentDataInstance;
}