#include "VSPuzzleABehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/VoidStar/HexusPoolVSGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VSPuzzleABehavior::MapKey = "vs-puzzle-A";

VSPuzzleABehavior* VSPuzzleABehavior::create(GameObject* owner)
{
	VSPuzzleABehavior* instance = new VSPuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

VSPuzzleABehavior::VSPuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

VSPuzzleABehavior::~VSPuzzleABehavior()
{
}

MinMaxPool* VSPuzzleABehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolVSGeneric::create(properties);
}

std::string VSPuzzleABehavior::getWinLossSaveKey()
{
	return VSPuzzleABehavior::MapKey;
}

std::string VSPuzzleABehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameVoidStar;
}

std::vector<CardData*> VSPuzzleABehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* VSPuzzleABehavior::getStateOverride()
{
	return StateOverride::create(
		// Player losses
		1,
		// Enemy losses
		1,
		// Player's turn
		true,
		// Player passed
		false,
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

std::vector<TutorialBase*> VSPuzzleABehavior::getTutorials()
{
	return { };
}
