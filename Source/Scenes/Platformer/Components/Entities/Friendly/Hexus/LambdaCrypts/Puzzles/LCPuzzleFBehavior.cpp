#include "LCPuzzleFBehavior.h"

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

const std::string LCPuzzleFBehavior::MapKey = "lc-puzzle-F";

LCPuzzleFBehavior* LCPuzzleFBehavior::create(GameObject* owner)
{
	LCPuzzleFBehavior* instance = new LCPuzzleFBehavior(owner);

	instance->autorelease();

	return instance;
}

LCPuzzleFBehavior::LCPuzzleFBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

LCPuzzleFBehavior::~LCPuzzleFBehavior()
{
}

MinMaxPool* LCPuzzleFBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string LCPuzzleFBehavior::getWinLossSaveKey()
{
	return LCPuzzleFBehavior::MapKey;
}

std::string LCPuzzleFBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> LCPuzzleFBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* LCPuzzleFBehavior::getStateOverride()
{
	// Needs work. Ideal effect is to keep shifting a card to AND it with other cards, then AND to zero out opponent cards
	// In practice this doesn't work so well
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
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
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
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
		}
	);
}

std::vector<TutorialBase*> LCPuzzleFBehavior::getTutorials()
{
	return { };
}
