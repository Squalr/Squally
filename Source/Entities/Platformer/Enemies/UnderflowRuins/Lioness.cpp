#include "Lioness.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/UnderflowRuins/Lioness.h"

using namespace cocos2d;

const std::string Lioness::MapKeyLioness = "lioness";
HexusOpponentData* Lioness::HexusOpponentDataInstance = nullptr;
const std::string Lioness::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIONESS";

Lioness* Lioness::deserialize(ValueMap& properties)
{
	Lioness* instance = new Lioness(properties);

	instance->autorelease();

	return instance;
}

Lioness::Lioness(ValueMap& properties) : super(properties,
	Lioness::MapKeyLioness,
	nullptr,
	EntityResources::Enemies_UnderflowRuins_Lioness_Emblem,
	Size(128.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Lioness::getHexusOpponentData();
}

Lioness::~Lioness()
{
}

Vec2 Lioness::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* Lioness::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Lioness::create();
}

HexusOpponentData* Lioness::getHexusOpponentData()
{
	if (Lioness::HexusOpponentDataInstance == nullptr)
	{
		Lioness::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -160.0f),
			Lioness::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.250f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
				}
			)
		);
	}

	return Lioness::HexusOpponentDataInstance;
}