#include "LCPuzzleBBehavior.h"

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

const std::string LCPuzzleBBehavior::MapKey = "lc-puzzle-B";

LCPuzzleBBehavior* LCPuzzleBBehavior::create(GameObject* owner)
{
	LCPuzzleBBehavior* instance = new LCPuzzleBBehavior(owner);

	instance->autorelease();

	return instance;
}

LCPuzzleBBehavior::LCPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

LCPuzzleBBehavior::~LCPuzzleBBehavior()
{
}

MinMaxPool* LCPuzzleBBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string LCPuzzleBBehavior::getWinLossSaveKey()
{
	return LCPuzzleBBehavior::MapKey;
}

std::string LCPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> LCPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* LCPuzzleBBehavior::getStateOverride()
{
	/*
	- Xor self 10 with 10
	- Flip self 10 to 5
	- Xor self 5 with 10
	- Flip self 5 to 10
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
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal10),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
		}
	);
}

std::vector<TutorialBase*> LCPuzzleBBehavior::getTutorials()
{
	return { };
}
