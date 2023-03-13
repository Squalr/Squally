#include "CVPuzzleBBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/CastleValgrind/HexusPoolCVGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CVPuzzleBBehavior::MapKey = "cv-puzzle-B";

CVPuzzleBBehavior* CVPuzzleBBehavior::create(GameObject* owner)
{
	CVPuzzleBBehavior* instance = new CVPuzzleBBehavior(owner);

	instance->autorelease();

	return instance;
}

CVPuzzleBBehavior::CVPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

CVPuzzleBBehavior::~CVPuzzleBBehavior()
{
}

MinMaxPool* CVPuzzleBBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string CVPuzzleBBehavior::getWinLossSaveKey()
{
	return CVPuzzleBBehavior::MapKey;
}

std::string CVPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> CVPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* CVPuzzleBBehavior::getStateOverride()
{
	/*
	- AND enemy b011
	*/
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
		// Player graveyard
		std::vector<CardData*>
		{
			
		},
		// Enemy graveyard
		std::vector<CardData*>
		{
			
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
		},
		// Player hex cards
		std::vector<CardData*>
		{
			
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
		}
	);
}

std::vector<TutorialBase*> CVPuzzleBBehavior::getTutorials()
{
	return { };
}
