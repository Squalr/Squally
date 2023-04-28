#include "FFPuzzleGBehavior.h"

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

const std::string FFPuzzleGBehavior::MapKey = "ff-puzzle-G";

FFPuzzleGBehavior* FFPuzzleGBehavior::create(GameObject* owner)
{
	FFPuzzleGBehavior* instance = new FFPuzzleGBehavior(owner);

	instance->autorelease();

	return instance;
}

FFPuzzleGBehavior::FFPuzzleGBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

FFPuzzleGBehavior::~FFPuzzleGBehavior()
{
}

MinMaxPool* FFPuzzleGBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolFFGeneric::create(properties);
}

std::string FFPuzzleGBehavior::getWinLossSaveKey()
{
	return FFPuzzleGBehavior::MapKey;
}

std::string FFPuzzleGBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameFirewallFissure;
}

std::vector<CardData*> FFPuzzleGBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* FFPuzzleGBehavior::getStateOverride()
{
	// AND enemy 5
	// Invert player 5
	// OR 10 onto 5 => 15
	// XOR 15 to enemy 15
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
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
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
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
		}
	);
}

std::vector<TutorialBase*> FFPuzzleGBehavior::getTutorials()
{
	return { };
}
