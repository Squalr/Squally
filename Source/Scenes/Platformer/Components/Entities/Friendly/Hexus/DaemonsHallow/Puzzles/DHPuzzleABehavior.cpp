#include "DHPuzzleABehavior.h"

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

const std::string DHPuzzleABehavior::MapKey = "dh-puzzle-A";

DHPuzzleABehavior* DHPuzzleABehavior::create(GameObject* owner)
{
	DHPuzzleABehavior* instance = new DHPuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

DHPuzzleABehavior::DHPuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DHPuzzleABehavior::~DHPuzzleABehavior()
{
}

MinMaxPool* DHPuzzleABehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string DHPuzzleABehavior::getWinLossSaveKey()
{
	return DHPuzzleABehavior::MapKey;
}

std::string DHPuzzleABehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> DHPuzzleABehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DHPuzzleABehavior::getStateOverride()
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
			// zzzzzz
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
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

std::vector<TutorialBase*> DHPuzzleABehavior::getTutorials()
{
	return { };
}
