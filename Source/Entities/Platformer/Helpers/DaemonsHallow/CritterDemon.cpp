#include "CritterDemon.h"

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

const std::string CritterDemon::MapKeyCritterDemon = "critter-demon";
HexusOpponentData* CritterDemon::HexusOpponentDataInstance = nullptr;
const std::string CritterDemon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CRITTER_DEMON";

CritterDemon* CritterDemon::deserialize(ValueMap& properties)
{
	CritterDemon* instance = new CritterDemon(properties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(ValueMap& properties) : super(properties,
	CritterDemon::MapKeyCritterDemon,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Animations,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Emblem,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = CritterDemon::getHexusOpponentData();
}

CritterDemon::~CritterDemon()
{
}

Vec2 CritterDemon::getDialogueOffset()
{
	return Vec2(-48.0f, -112.0f);
}

LocalizedString* CritterDemon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_DaemonsHallow_CritterDemon::create();
}

HexusOpponentData* CritterDemon::getHexusOpponentData()
{
	if (CritterDemon::HexusOpponentDataInstance == nullptr)
	{
		CritterDemon::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-48.0f, -112.0f),
			CritterDemon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 1.000f,
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
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
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

	return CritterDemon::HexusOpponentDataInstance;
}