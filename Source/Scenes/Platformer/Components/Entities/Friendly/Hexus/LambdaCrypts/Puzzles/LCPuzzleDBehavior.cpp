#include "LCPuzzleDBehavior.h"

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

const std::string LCPuzzleDBehavior::MapKey = "lc-puzzle-D";

LCPuzzleDBehavior* LCPuzzleDBehavior::create(GameObject* owner)
{
	LCPuzzleDBehavior* instance = new LCPuzzleDBehavior(owner);

	instance->autorelease();

	return instance;
}

LCPuzzleDBehavior::LCPuzzleDBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

LCPuzzleDBehavior::~LCPuzzleDBehavior()
{
}

MinMaxPool* LCPuzzleDBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string LCPuzzleDBehavior::getWinLossSaveKey()
{
	return LCPuzzleDBehavior::MapKey;
}

std::string LCPuzzleDBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> LCPuzzleDBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* LCPuzzleDBehavior::getStateOverride()
{
	/*
	- Invert a 7 into 8
	- MOV the 8 to their row
	- SHL that row to oblivion
	*/
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
			CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
		}
	);
}

std::vector<TutorialBase*> LCPuzzleDBehavior::getTutorials()
{
	return { };
}
