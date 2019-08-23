#include "AnubisPup.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/UnderflowRuins/AnubisPup.h"

using namespace cocos2d;

const std::string AnubisPup::MapKeyAnubisPup = "anubis-pup";
HexusOpponentData* AnubisPup::HexusOpponentDataInstance = nullptr;
const std::string AnubisPup::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ANUBIS_PUP";

AnubisPup* AnubisPup::deserialize(ValueMap& properties)
{
	AnubisPup* instance = new AnubisPup(properties);

	instance->autorelease();

	return instance;
}

AnubisPup::AnubisPup(ValueMap& properties) : super(properties,
	AnubisPup::MapKeyAnubisPup,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisPup_Emblem,
	Size(128.0f, 186.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = AnubisPup::getHexusOpponentData();
}

AnubisPup::~AnubisPup()
{
}

Vec2 AnubisPup::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* AnubisPup::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_AnubisPup::create();
}

HexusOpponentData* AnubisPup::getHexusOpponentData()
{
	if (AnubisPup::HexusOpponentDataInstance == nullptr)
	{
		AnubisPup::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_AnubisPup_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			AnubisPup::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.083f,
			HexusOpponentData::generateDeck(32, 0.083f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return AnubisPup::HexusOpponentDataInstance;
}