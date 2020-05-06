#include "URPuzzleFBehavior.h"

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

const std::string URPuzzleFBehavior::MapKey = "ur-puzzle-F";

URPuzzleFBehavior* URPuzzleFBehavior::create(GameObject* owner)
{
	URPuzzleFBehavior* instance = new URPuzzleFBehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleFBehavior::URPuzzleFBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

URPuzzleFBehavior::~URPuzzleFBehavior()
{
}

MinMaxPool* URPuzzleFBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string URPuzzleFBehavior::getWinLossSaveKey()
{
	return URPuzzleFBehavior::MapKey;
}

std::string URPuzzleFBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> URPuzzleFBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* URPuzzleFBehavior::getStateOverride()
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
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			
		}
	);
}

std::vector<TutorialBase*> URPuzzleFBehavior::getTutorials()
{
	return { };
}
