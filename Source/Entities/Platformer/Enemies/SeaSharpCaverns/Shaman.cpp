#include "Shaman.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/SeaSharpCaverns/Shaman.h"

using namespace cocos2d;

const std::string Shaman::MapKeyShaman = "shaman";
HexusOpponentData* Shaman::HexusOpponentDataInstance = nullptr;
const std::string Shaman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHAMAN";

Shaman* Shaman::deserialize(ValueMap& properties)
{
	Shaman* instance = new Shaman(properties);

	instance->autorelease();

	return instance;
}

Shaman::Shaman(ValueMap& properties) : super(properties,
	Shaman::MapKeyShaman,
	EntityResources::Enemies_SeaSharpCaverns_Shaman_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Shaman_Emblem,
	Size(256.0f, 288.0f),
	0.78f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Shaman::getHexusOpponentData();
}

Shaman::~Shaman()
{
}

Vec2 Shaman::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Shaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_Shaman::create();
}

HexusOpponentData* Shaman::getHexusOpponentData()
{
	if (Shaman::HexusOpponentDataInstance == nullptr)
	{
		Shaman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_Shaman_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			0.78f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Shaman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Mov),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Shaman::HexusOpponentDataInstance;
}