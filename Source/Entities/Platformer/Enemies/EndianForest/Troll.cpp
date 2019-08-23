#include "Troll.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/Troll.h"

using namespace cocos2d;

const std::string Troll::MapKeyTroll = "troll";
HexusOpponentData* Troll::HexusOpponentDataInstance = nullptr;
const std::string Troll::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TROLL";

Troll* Troll::deserialize(ValueMap& properties)
{
	Troll* instance = new Troll(properties);

	instance->autorelease();

	return instance;
}

Troll::Troll(ValueMap& properties) : super(properties,
	Troll::MapKeyTroll,
	EntityResources::Enemies_EndianForest_Troll_Animations,
	EntityResources::Enemies_EndianForest_Troll_Emblem,
	Size(256.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Troll::getHexusOpponentData();
}

Troll::~Troll()
{
}

Vec2 Troll::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Troll::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Troll::create();
}

HexusOpponentData* Troll::getHexusOpponentData()
{
	if (Troll::HexusOpponentDataInstance == nullptr)
	{
		Troll::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Troll_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Troll::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.923f,
			HexusOpponentData::generateDeck(32, 0.923f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::Mov),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
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
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Troll::HexusOpponentDataInstance;
}