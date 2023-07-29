#include "URPuzzleABehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/UnderflowRuins/HexusPoolURGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string URPuzzleABehavior::MapKey = "ur-puzzle-A";

URPuzzleABehavior* URPuzzleABehavior::create(GameObject* owner)
{
	URPuzzleABehavior* instance = new URPuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleABehavior::URPuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

URPuzzleABehavior::~URPuzzleABehavior()
{
}

MinMaxPool* URPuzzleABehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolURGeneric::create(properties);
}

std::string URPuzzleABehavior::getWinLossSaveKey()
{
	return URPuzzleABehavior::MapKey;
}

std::string URPuzzleABehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameUnderflowRuins;
}

std::vector<CardData*> URPuzzleABehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* URPuzzleABehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
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
		}
	);
}

std::vector<TutorialBase*> URPuzzleABehavior::getTutorials()
{
	return { };
}
