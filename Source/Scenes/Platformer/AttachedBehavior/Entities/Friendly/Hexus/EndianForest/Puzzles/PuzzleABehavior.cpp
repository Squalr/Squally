#include "PuzzleABehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolEFGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PuzzleABehavior::MapKeyAttachedBehavior = "puzzle-A";

PuzzleABehavior* PuzzleABehavior::create(GameObject* owner)
{
	PuzzleABehavior* instance = new PuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

PuzzleABehavior::PuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

PuzzleABehavior::~PuzzleABehavior()
{
}

MinMaxPool* PuzzleABehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string PuzzleABehavior::getWinLossSaveKey()
{
	return PuzzleABehavior::MapKeyAttachedBehavior;
}

std::string PuzzleABehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> PuzzleABehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* PuzzleABehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			
		}
	);
}

std::vector<TutorialBase*> PuzzleABehavior::getTutorials()
{
	return { };
}
