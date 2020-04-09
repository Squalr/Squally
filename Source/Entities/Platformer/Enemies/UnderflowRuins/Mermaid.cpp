#include "Mermaid.h"

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

const std::string Mermaid::MapKey = "mermaid";
HexusOpponentData* Mermaid::HexusOpponentDataInstance = nullptr;
const std::string Mermaid::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MERMAID";

Mermaid* Mermaid::deserialize(ValueMap& properties)
{
	Mermaid* instance = new Mermaid(properties);

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid(ValueMap& properties) : super(properties,
	Mermaid::MapKey,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Animations,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Emblem,
	Size(172.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Mermaid::getHexusOpponentData();
}

Mermaid::~Mermaid()
{
}

Vec2 Mermaid::getDialogueOffset()
{
	return Vec2(-32.0f, -180.0f);
}

LocalizedString* Mermaid::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Mermaid::create();
}

HexusOpponentData* Mermaid::getHexusOpponentData()
{
	if (Mermaid::HexusOpponentDataInstance == nullptr)
	{
		Mermaid::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -180.0f),
			Mermaid::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.750f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
				}
			)
		);
	}

	return Mermaid::HexusOpponentDataInstance;
}