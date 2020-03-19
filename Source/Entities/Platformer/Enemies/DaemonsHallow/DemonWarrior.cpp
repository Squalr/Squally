#include "DemonWarrior.h"

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

const std::string DemonWarrior::MapKey = "demon-warrior";
HexusOpponentData* DemonWarrior::HexusOpponentDataInstance = nullptr;
const std::string DemonWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_WARRIOR";

DemonWarrior* DemonWarrior::deserialize(ValueMap& properties)
{
	DemonWarrior* instance = new DemonWarrior(properties);

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior(ValueMap& properties) : super(properties,
	DemonWarrior::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Emblem,
	Size(320.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = DemonWarrior::getHexusOpponentData();
}

DemonWarrior::~DemonWarrior()
{
}

Vec2 DemonWarrior::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonWarrior::create();
}

HexusOpponentData* DemonWarrior::getHexusOpponentData()
{
	if (DemonWarrior::HexusOpponentDataInstance == nullptr)
	{
		DemonWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			DemonWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.583f,
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

	return DemonWarrior::HexusOpponentDataInstance;
}