#include "DHPuzzleCBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/DaemonsHallow/HexusPoolDHGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DHPuzzleCBehavior::MapKey = "dh-puzzle-C";

DHPuzzleCBehavior* DHPuzzleCBehavior::create(GameObject* owner)
{
	DHPuzzleCBehavior* instance = new DHPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

DHPuzzleCBehavior::DHPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DHPuzzleCBehavior::~DHPuzzleCBehavior()
{
}

MinMaxPool* DHPuzzleCBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string DHPuzzleCBehavior::getWinLossSaveKey()
{
	return DHPuzzleCBehavior::MapKey;
}

std::string DHPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> DHPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DHPuzzleCBehavior::getStateOverride()
{
	return StateOverride::create(
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
		// Player graveyard
		std::vector<CardData*>
		{
			
		},
		// Enemy graveyard
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
	);
}

std::vector<TutorialBase*> DHPuzzleCBehavior::getTutorials()
{
	return { };
}
