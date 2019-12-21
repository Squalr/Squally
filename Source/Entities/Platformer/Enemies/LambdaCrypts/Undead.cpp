#include "Undead.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Undead::MapKeyUndead = "undead";
HexusOpponentData* Undead::HexusOpponentDataInstance = nullptr;
const std::string Undead::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_UNDEAD";

Undead* Undead::deserialize(ValueMap& properties)
{
	Undead* instance = new Undead(properties);

	instance->autorelease();

	return instance;
}

Undead::Undead(ValueMap& properties) : super(properties,
	Undead::MapKeyUndead,
	EntityResources::Enemies_LambdaCrypts_Undead_Animations,
	EntityResources::Enemies_LambdaCrypts_Undead_Emblem,
	Size(146.0f, 248.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Undead::getHexusOpponentData();
}

Undead::~Undead()
{
}

Vec2 Undead::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Undead::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Undead::create();
}

HexusOpponentData* Undead::getHexusOpponentData()
{
	if (Undead::HexusOpponentDataInstance == nullptr)
	{
		Undead::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Undead::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.167f,
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

	return Undead::HexusOpponentDataInstance;
}