#include "FFPuzzleBBehavior.h"

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

const std::string FFPuzzleBBehavior::MapKey = "ff-puzzle-B";

FFPuzzleBBehavior* FFPuzzleBBehavior::create(GameObject* owner)
{
	FFPuzzleBBehavior* instance = new FFPuzzleBBehavior(owner);

	instance->autorelease();

	return instance;
}

FFPuzzleBBehavior::FFPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

FFPuzzleBBehavior::~FFPuzzleBBehavior()
{
}

MinMaxPool* FFPuzzleBBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolFFGeneric::create(properties);
}

std::string FFPuzzleBBehavior::getWinLossSaveKey()
{
	return FFPuzzleBBehavior::MapKey;
}

std::string FFPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameFirewallFissure;
}

std::vector<CardData*> FFPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* FFPuzzleBBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			 // Flip 4
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			 // Flip 2
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			 // Flip 3
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal14),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
		}
	);
}

std::vector<TutorialBase*> FFPuzzleBBehavior::getTutorials()
{
	return { };
}
