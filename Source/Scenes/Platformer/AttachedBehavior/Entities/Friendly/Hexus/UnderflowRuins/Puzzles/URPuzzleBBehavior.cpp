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

URPuzzleBBehavior::URPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

URPuzzleBBehavior::~URPuzzleBBehavior()
{
}

MinMaxPool* URPuzzleBBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string URPuzzleBBehavior::getWinLossSaveKey()
{
	return URPuzzleBBehavior::MapKey;
}

std::string URPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> URPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
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

std::vector<TutorialBase*> URPuzzleBBehavior::getTutorials()
{
	return { TutorialPuzzleB::create() };
}
