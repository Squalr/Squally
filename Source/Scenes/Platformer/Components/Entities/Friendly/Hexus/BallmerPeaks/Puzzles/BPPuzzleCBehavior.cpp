#include "BPPuzzleCBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/BallmerPeaks/HexusPoolBPGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BPPuzzleCBehavior::MapKey = "bp-puzzle-C";

BPPuzzleCBehavior* BPPuzzleCBehavior::create(GameObject* owner)
{
	BPPuzzleCBehavior* instance = new BPPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

BPPuzzleCBehavior::BPPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

BPPuzzleCBehavior::~BPPuzzleCBehavior()
{
}

MinMaxPool* BPPuzzleCBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolBPGeneric::create(properties);
}

std::string BPPuzzleCBehavior::getWinLossSaveKey()
{
	return BPPuzzleCBehavior::MapKey;
}

std::string BPPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameBallmerPeaks;
}

std::vector<CardData*> BPPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* BPPuzzleCBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::Steal),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
		}
	);
}

std::vector<TutorialBase*> BPPuzzleCBehavior::getTutorials()
{
	return { };
}
