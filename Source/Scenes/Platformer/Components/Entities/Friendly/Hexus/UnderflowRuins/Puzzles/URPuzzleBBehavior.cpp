#include "URPuzzleBBehavior.h"

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

const std::string URPuzzleBBehavior::MapKey = "ur-puzzle-B";

URPuzzleBBehavior* URPuzzleBBehavior::create(GameObject* owner)
{
	URPuzzleBBehavior* instance = new URPuzzleBBehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleBBehavior::URPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

URPuzzleBBehavior::~URPuzzleBBehavior()
{
}

MinMaxPool* URPuzzleBBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolURGeneric::create(properties);
}

std::string URPuzzleBBehavior::getWinLossSaveKey()
{
	return URPuzzleBBehavior::MapKey;
}

std::string URPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameUnderflowRuins;
}

std::vector<CardData*> URPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* URPuzzleBBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
		}
	);
}

std::vector<TutorialBase*> URPuzzleBBehavior::getTutorials()
{
	return { };
}
