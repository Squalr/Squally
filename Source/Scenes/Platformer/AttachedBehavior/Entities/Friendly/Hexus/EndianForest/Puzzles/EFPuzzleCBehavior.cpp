#include "EFPuzzleCBehavior.h"

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

const std::string EFPuzzleCBehavior::MapKey = "ef-puzzle-C";

EFPuzzleCBehavior* EFPuzzleCBehavior::create(GameObject* owner)
{
	EFPuzzleCBehavior* instance = new EFPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

EFPuzzleCBehavior::EFPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

EFPuzzleCBehavior::~EFPuzzleCBehavior()
{
}

MinMaxPool* EFPuzzleCBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string EFPuzzleCBehavior::getWinLossSaveKey()
{
	return EFPuzzleCBehavior::MapKey;
}

std::string EFPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> EFPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* EFPuzzleCBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
		}
	);
}

std::vector<TutorialBase*> EFPuzzleCBehavior::getTutorials()
{
	return { TutorialPuzzleC::create() };
}
