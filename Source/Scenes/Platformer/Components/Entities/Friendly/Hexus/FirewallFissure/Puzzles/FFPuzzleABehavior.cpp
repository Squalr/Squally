#include "FFPuzzleABehavior.h"

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

const std::string FFPuzzleABehavior::MapKey = "ff-puzzle-A";

FFPuzzleABehavior* FFPuzzleABehavior::create(GameObject* owner)
{
	FFPuzzleABehavior* instance = new FFPuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

FFPuzzleABehavior::FFPuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

FFPuzzleABehavior::~FFPuzzleABehavior()
{
}

MinMaxPool* FFPuzzleABehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolFFGeneric::create(properties);
}

std::string FFPuzzleABehavior::getWinLossSaveKey()
{
	return FFPuzzleABehavior::MapKey;
}

std::string FFPuzzleABehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameFirewallFissure;
}

std::vector<CardData*> FFPuzzleABehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* FFPuzzleABehavior::getStateOverride()
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
		false,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
		},
		// Player binary cards
		std::vector<CardData*>
		{
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
		}
	);
}

std::vector<TutorialBase*> FFPuzzleABehavior::getTutorials()
{
	return { };
}
