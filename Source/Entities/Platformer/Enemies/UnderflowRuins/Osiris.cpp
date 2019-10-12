#include "Osiris.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/UnderflowRuins/Osiris.h"

using namespace cocos2d;

const std::string Osiris::MapKeyOsiris = "osiris";
HexusOpponentData* Osiris::HexusOpponentDataInstance = nullptr;
const std::string Osiris::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_OSIRIS";

Osiris* Osiris::deserialize(ValueMap& properties)
{
	Osiris* instance = new Osiris(properties);

	instance->autorelease();

	return instance;
}

Osiris::Osiris(ValueMap& properties) : super(properties,
	Osiris::MapKeyOsiris,
	EntityResources::Enemies_UnderflowRuins_Osiris_Animations,
	EntityResources::Enemies_UnderflowRuins_Osiris_Emblem,
	Size(324.0f, 316.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Osiris::getHexusOpponentData();
}

Osiris::~Osiris()
{
}

Vec2 Osiris::getDialogueOffset()
{
	return Vec2(-32.0f, -212.0f);
}

LocalizedString* Osiris::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Osiris::create();
}

HexusOpponentData* Osiris::getHexusOpponentData()
{
	if (Osiris::HexusOpponentDataInstance == nullptr)
	{
		Osiris::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Osiris_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -212.0f),
			Osiris::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
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

	return Osiris::HexusOpponentDataInstance;
}