#include "DMPuzzleDBehavior.h"

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

const std::string DMPuzzleDBehavior::MapKey = "dm-puzzle-D";

DMPuzzleDBehavior* DMPuzzleDBehavior::create(GameObject* owner)
{
	DMPuzzleDBehavior* instance = new DMPuzzleDBehavior(owner);

	instance->autorelease();

	return instance;
}

DMPuzzleDBehavior::DMPuzzleDBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DMPuzzleDBehavior::~DMPuzzleDBehavior()
{
}

MinMaxPool* DMPuzzleDBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string DMPuzzleDBehavior::getWinLossSaveKey()
{
	return DMPuzzleDBehavior::MapKey;
}

std::string DMPuzzleDBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> DMPuzzleDBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DMPuzzleDBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
		}
	);
}

std::vector<TutorialBase*> DMPuzzleDBehavior::getTutorials()
{
	return { };
}
