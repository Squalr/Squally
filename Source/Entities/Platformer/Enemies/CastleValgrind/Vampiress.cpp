#include "Vampiress.h"

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

const std::string Vampiress::MapKey = "vampiress";
HexusOpponentData* Vampiress::HexusOpponentDataInstance = nullptr;
const std::string Vampiress::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VAMPIRESS";

Vampiress* Vampiress::deserialize(ValueMap& properties)
{
	Vampiress* instance = new Vampiress(properties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(ValueMap& properties) : super(properties,
	Vampiress::MapKey,
	EntityResources::Enemies_CastleValgrind_Vampiress_Animations,
	EntityResources::Enemies_CastleValgrind_Vampiress_Emblem,
	Size(96.0f, 236.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Vampiress::getHexusOpponentData();
}

Vampiress::~Vampiress()
{
}

Vec2 Vampiress::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Vampiress::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Vampiress::create();
}

HexusOpponentData* Vampiress::getHexusOpponentData()
{
	if (Vampiress::HexusOpponentDataInstance == nullptr)
	{
		Vampiress::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Vampiress::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.417f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
					CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				}
			)
		);
	}

	return Vampiress::HexusOpponentDataInstance;
}