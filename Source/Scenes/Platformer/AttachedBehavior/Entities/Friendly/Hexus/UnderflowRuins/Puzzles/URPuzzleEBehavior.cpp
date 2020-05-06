#include "URPuzzleEBehavior.h"

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

const std::string URPuzzleEBehavior::MapKey = "ur-puzzle-E";

URPuzzleEBehavior* URPuzzleEBehavior::create(GameObject* owner)
{
	URPuzzleEBehavior* instance = new URPuzzleEBehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleEBehavior::URPuzzleEBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

URPuzzleEBehavior::~URPuzzleEBehavior()
{
}

MinMaxPool* URPuzzleEBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string URPuzzleEBehavior::getWinLossSaveKey()
{
	return URPuzzleEBehavior::MapKey;
}

std::string URPuzzleEBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> URPuzzleEBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* URPuzzleEBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
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
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
		}
	);
}

std::vector<TutorialBase*> URPuzzleEBehavior::getTutorials()
{
	return { };
}
