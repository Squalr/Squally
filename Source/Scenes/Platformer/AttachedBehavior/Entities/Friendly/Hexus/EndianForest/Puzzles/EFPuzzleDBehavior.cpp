#include "EFPuzzleDBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolEFGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EFPuzzleDBehavior::MapKey = "ef-puzzle-D";

EFPuzzleDBehavior* EFPuzzleDBehavior::create(GameObject* owner)
{
	EFPuzzleDBehavior* instance = new EFPuzzleDBehavior(owner);

	instance->autorelease();

	return instance;
}

EFPuzzleDBehavior::EFPuzzleDBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

EFPuzzleDBehavior::~EFPuzzleDBehavior()
{
}

MinMaxPool* EFPuzzleDBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string EFPuzzleDBehavior::getWinLossSaveKey()
{
	return EFPuzzleDBehavior::MapKey;
}

std::string EFPuzzleDBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> EFPuzzleDBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* EFPuzzleDBehavior::getStateOverride()
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
			
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
		}
	);
}

std::vector<TutorialBase*> EFPuzzleDBehavior::getTutorials()
{
	return { TutorialPuzzleShlOverflow::create() };
}
