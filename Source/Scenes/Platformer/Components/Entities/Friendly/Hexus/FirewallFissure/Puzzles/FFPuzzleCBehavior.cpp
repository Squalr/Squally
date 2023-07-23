#include "FFPuzzleCBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/FirewallFissure/HexusPoolFFGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FFPuzzleCBehavior::MapKey = "ff-puzzle-C";

FFPuzzleCBehavior* FFPuzzleCBehavior::create(GameObject* owner)
{
	FFPuzzleCBehavior* instance = new FFPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

FFPuzzleCBehavior::FFPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

FFPuzzleCBehavior::~FFPuzzleCBehavior()
{
}

MinMaxPool* FFPuzzleCBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolFFGeneric::create(properties);
}

std::string FFPuzzleCBehavior::getWinLossSaveKey()
{
	return FFPuzzleCBehavior::MapKey;
}

std::string FFPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameFirewallFissure;
}

std::vector<CardData*> FFPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* FFPuzzleCBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
		}
	);
}

std::vector<TutorialBase*> FFPuzzleCBehavior::getTutorials()
{
	return { };
}
