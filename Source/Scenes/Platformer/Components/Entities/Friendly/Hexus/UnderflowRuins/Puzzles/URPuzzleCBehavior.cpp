#include "URPuzzleCBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/UnderflowRuins/HexusPoolURGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string URPuzzleCBehavior::MapKey = "ur-puzzle-C";

URPuzzleCBehavior* URPuzzleCBehavior::create(GameObject* owner)
{
	URPuzzleCBehavior* instance = new URPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleCBehavior::URPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

URPuzzleCBehavior::~URPuzzleCBehavior()
{
}

MinMaxPool* URPuzzleCBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolURGeneric::create(properties);
}

std::string URPuzzleCBehavior::getWinLossSaveKey()
{
	return URPuzzleCBehavior::MapKey;
}

std::string URPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameUnderflowRuins;
}

std::vector<CardData*> URPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* URPuzzleCBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			
		}
	);
}

std::vector<TutorialBase*> URPuzzleCBehavior::getTutorials()
{
	return { };
}
