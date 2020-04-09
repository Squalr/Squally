#include "Jack.h"

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

const std::string Jack::MapKey = "jack";
HexusOpponentData* Jack::HexusOpponentDataInstance = nullptr;
const std::string Jack::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JACK";

Jack* Jack::deserialize(ValueMap& properties)
{
	Jack* instance = new Jack(properties);

	instance->autorelease();

	return instance;
}

Jack::Jack(ValueMap& properties) : super(properties,
	Jack::MapKey,
	EntityResources::Enemies_CastleValgrind_Jack_Animations,
	EntityResources::Enemies_CastleValgrind_Jack_Emblem,
	Size(432.0f, 768.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Jack::getHexusOpponentData();
}

Jack::~Jack()
{
}

Vec2 Jack::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Jack::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Jack::create();
}

HexusOpponentData* Jack::getHexusOpponentData()
{
	if (Jack::HexusOpponentDataInstance == nullptr)
	{
		Jack::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Jack::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.917f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
					CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
				}
			)
		);
	}

	return Jack::HexusOpponentDataInstance;
}