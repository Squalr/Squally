#include "LCPuzzleEBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/LambdaCrypts/HexusPoolLCGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LCPuzzleEBehavior::MapKey = "lc-puzzle-E";

LCPuzzleEBehavior* LCPuzzleEBehavior::create(GameObject* owner)
{
	LCPuzzleEBehavior* instance = new LCPuzzleEBehavior(owner);

	instance->autorelease();

	return instance;
}

LCPuzzleEBehavior::LCPuzzleEBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

LCPuzzleEBehavior::~LCPuzzleEBehavior()
{
}

MinMaxPool* LCPuzzleEBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string LCPuzzleEBehavior::getWinLossSaveKey()
{
	return LCPuzzleEBehavior::MapKey;
}

std::string LCPuzzleEBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> LCPuzzleEBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* LCPuzzleEBehavior::getStateOverride()
{
	/*
	- Enemy ANDs, zeroing out player Dec card
	- Enemy Flip2, zeroing out player Hex card
	- Player ANDs this against enemy 14 (zeroing)
	- Player clears Dec card
	- Player adds Dec to enemy Dec, overflowing to 0
	*/
	return StateOverride::create(
		// Player losses
		1,
		// Enemy losses
		1,
		// Player's turn
		false,
		// Player passed
		false,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Clear),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
		}
	);
}

std::vector<TutorialBase*> LCPuzzleEBehavior::getTutorials()
{
	return { };
}
