#include "Barbarian.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Barbarian::MapKeyBarbarian = "barbarian";
HexusOpponentData* Barbarian::HexusOpponentDataInstance = nullptr;
const std::string Barbarian::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BARBARIAN";

Barbarian* Barbarian::deserialize(ValueMap& properties)
{
	Barbarian* instance = new Barbarian(properties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(ValueMap& properties) : super(properties,
	Barbarian::MapKeyBarbarian,
	EntityResources::Enemies_SeaSharpCaverns_Barbarian_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Barbarian_Emblem,
	Size(1280.0f, 920.0f),
	1.0f,
	Vec2(-32.0f, 0.0f))
{
	this->hexusOpponentData = Barbarian::getHexusOpponentData();
}

Barbarian::~Barbarian()
{
}

Vec2 Barbarian::getDialogueOffset()
{
	return Vec2(0.0f, -160.0f);
}

LocalizedString* Barbarian::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_Barbarian::create();
}

HexusOpponentData* Barbarian::getHexusOpponentData()
{
	if (Barbarian::HexusOpponentDataInstance == nullptr)
	{
		Barbarian::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(0.0f, -160.0f),
			Barbarian::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.083f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
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

	return Barbarian::HexusOpponentDataInstance;
}