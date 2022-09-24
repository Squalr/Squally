#include "DMPuzzleEBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/DataMines/HexusPoolDMGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DMPuzzleEBehavior::MapKey = "dm-puzzle-E";

DMPuzzleEBehavior* DMPuzzleEBehavior::create(GameObject* owner)
{
	DMPuzzleEBehavior* instance = new DMPuzzleEBehavior(owner);

	instance->autorelease();

	return instance;
}

DMPuzzleEBehavior::DMPuzzleEBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DMPuzzleEBehavior::~DMPuzzleEBehavior()
{
}

MinMaxPool* DMPuzzleEBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string DMPuzzleEBehavior::getWinLossSaveKey()
{
	return DMPuzzleEBehavior::MapKey;
}

std::string DMPuzzleEBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> DMPuzzleEBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DMPuzzleEBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
		}
	);
}

std::vector<TutorialBase*> DMPuzzleEBehavior::getTutorials()
{
	return { };
}
