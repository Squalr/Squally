#include "FFPuzzleEBehavior.h"

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

const std::string FFPuzzleEBehavior::MapKey = "ff-puzzle-E";

FFPuzzleEBehavior* FFPuzzleEBehavior::create(GameObject* owner)
{
	FFPuzzleEBehavior* instance = new FFPuzzleEBehavior(owner);

	instance->autorelease();

	return instance;
}

FFPuzzleEBehavior::FFPuzzleEBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

FFPuzzleEBehavior::~FFPuzzleEBehavior()
{
}

MinMaxPool* FFPuzzleEBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolFFGeneric::create(properties);
}

std::string FFPuzzleEBehavior::getWinLossSaveKey()
{
	return FFPuzzleEBehavior::MapKey;
}

std::string FFPuzzleEBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameFirewallFissure;
}

std::vector<CardData*> FFPuzzleEBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* FFPuzzleEBehavior::getStateOverride()
{
	/*
	- ROL strongest hex
	- Steal hex 5
	- SHL hex
	- OR E onto 0 dec
	- ROL 7 dec
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
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
		}
	);
}

std::vector<TutorialBase*> FFPuzzleEBehavior::getTutorials()
{
	return { };
}
