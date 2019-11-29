#include "PuzzleABehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/ComeToLearn.h"

using namespace cocos2d;

const std::string PuzzleABehavior::WinLossTrackIdentifier = "puzzle-A";

PuzzleABehavior* PuzzleABehavior::create(GameObject* owner)
{
	PuzzleABehavior* instance = new PuzzleABehavior(owner);

	instance->autorelease();

	return instance;
}

PuzzleABehavior::PuzzleABehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Quests_EndianForest_HexusGauntlet_ComeToLearn::create())
{
}

PuzzleABehavior::~PuzzleABehavior()
{
}

MinMaxPool* PuzzleABehavior::generateReward()
{
	return nullptr;
}

std::string PuzzleABehavior::getWinLossSaveKey()
{
	return PuzzleABehavior::WinLossTrackIdentifier;
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
		false,
		// Enemy passed
		true,
		// Player deck
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
		},
		// Enemy deck
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
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
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal11),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
		}
	);
}

std::vector<TutorialBase*> PuzzleABehavior::getTutorials()
{
	return { TutorialAIntroSequence::create(), TutorialACardStaged::create(), TutorialAVictory::create() };
}
