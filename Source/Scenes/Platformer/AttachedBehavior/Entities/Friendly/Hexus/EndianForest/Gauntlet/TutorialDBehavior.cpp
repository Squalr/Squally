#include "TutorialDBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/EmptyPool.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TutorialDBehavior::WinLossTrackIdentifier = "tutorial-D";

TutorialDBehavior* TutorialDBehavior::create(GameObject* owner)
{
	TutorialDBehavior* instance = new TutorialDBehavior(owner);

	instance->autorelease();

	return instance;
}

TutorialDBehavior::TutorialDBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Quests_EndianForest_HexusGauntlet_ComeToLearn::create())
{
}

TutorialDBehavior::~TutorialDBehavior()
{
}

MinMaxPool* TutorialDBehavior::generateReward()
{
	return EmptyPool::create();
}

std::string TutorialDBehavior::getWinLossSaveKey()
{
	return TutorialDBehavior::WinLossTrackIdentifier;
}

std::string TutorialDBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> TutorialDBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});;
}

StateOverride* TutorialDBehavior::getStateOverride()
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
		false,
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
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
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

std::vector<TutorialBase*> TutorialDBehavior::getTutorials()
{
	return { TutorialDIntroSequence::create() };
}
