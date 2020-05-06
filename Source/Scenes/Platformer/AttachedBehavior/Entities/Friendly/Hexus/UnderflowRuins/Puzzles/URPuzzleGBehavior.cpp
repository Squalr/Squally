#include "URPuzzleGBehavior.h"

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

const std::string URPuzzleGBehavior::MapKey = "ur-puzzle-G";

URPuzzleGBehavior* URPuzzleGBehavior::create(GameObject* owner)
{
	URPuzzleGBehavior* instance = new URPuzzleGBehavior(owner);

	instance->autorelease();

	return instance;
}

URPuzzleGBehavior::URPuzzleGBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

URPuzzleGBehavior::~URPuzzleGBehavior()
{
}

MinMaxPool* URPuzzleGBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string URPuzzleGBehavior::getWinLossSaveKey()
{
	return URPuzzleGBehavior::MapKey;
}

std::string URPuzzleGBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> URPuzzleGBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* URPuzzleGBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			CardList::getInstance()->cardListByName.at(CardKeys::Mov),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
		}
	);
}

std::vector<TutorialBase*> URPuzzleGBehavior::getTutorials()
{
	return { };
}
