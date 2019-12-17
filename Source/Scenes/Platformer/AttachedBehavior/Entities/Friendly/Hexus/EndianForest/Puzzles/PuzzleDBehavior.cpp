#include "PuzzleDBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
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

const std::string PuzzleDBehavior::MapKeyAttachedBehavior = "puzzle-D";

PuzzleDBehavior* PuzzleDBehavior::create(GameObject* owner)
{
	PuzzleDBehavior* instance = new PuzzleDBehavior(owner);

	instance->autorelease();

	return instance;
}

PuzzleDBehavior::PuzzleDBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
{
}

PuzzleDBehavior::~PuzzleDBehavior()
{
}

MinMaxPool* PuzzleDBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string PuzzleDBehavior::getWinLossSaveKey()
{
	return PuzzleDBehavior::MapKeyAttachedBehavior;
}

std::string PuzzleDBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> PuzzleDBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* PuzzleDBehavior::getStateOverride()
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

std::vector<TutorialBase*> PuzzleDBehavior::getTutorials()
{
	return { TutorialPuzzleD::create() };
}
