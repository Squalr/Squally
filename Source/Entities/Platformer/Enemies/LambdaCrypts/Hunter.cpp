#include "Hunter.h"

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

const std::string Hunter::MapKeyHunter = "hunter";
HexusOpponentData* Hunter::HexusOpponentDataInstance = nullptr;
const std::string Hunter::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HUNTER";

Hunter* Hunter::deserialize(ValueMap& properties)
{
	Hunter* instance = new Hunter(properties);

	instance->autorelease();

	return instance;
}

Hunter::Hunter(ValueMap& properties) : super(properties,
	Hunter::MapKeyHunter,
	EntityResources::Enemies_LambdaCrypts_Hunter_Animations,
	EntityResources::Enemies_LambdaCrypts_Hunter_Emblem,
	Size(112.0f, 596.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Hunter::getHexusOpponentData();
}

Hunter::~Hunter()
{
}

Vec2 Hunter::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Hunter::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Hunter::create();
}

HexusOpponentData* Hunter::getHexusOpponentData()
{
	if (Hunter::HexusOpponentDataInstance == nullptr)
	{
		Hunter::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Hunter::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return Hunter::HexusOpponentDataInstance;
}