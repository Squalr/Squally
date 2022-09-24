#include "DMPuzzleBBehavior.h"

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

const std::string DMPuzzleBBehavior::MapKey = "dm-puzzle-B";

DMPuzzleBBehavior* DMPuzzleBBehavior::create(GameObject* owner)
{
	DMPuzzleBBehavior* instance = new DMPuzzleBBehavior(owner);

	instance->autorelease();

	return instance;
}

DMPuzzleBBehavior::DMPuzzleBBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DMPuzzleBBehavior::~DMPuzzleBBehavior()
{
}

MinMaxPool* DMPuzzleBBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string DMPuzzleBBehavior::getWinLossSaveKey()
{
	return DMPuzzleBBehavior::MapKey;
}

std::string DMPuzzleBBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> DMPuzzleBBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DMPuzzleBBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Mov), // 10 vs enemy 5, mov to equalize, AND to smite
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight), // 8 vs enemy 4. Shr to equalize, AND to smite
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
		}
	);
}

std::vector<TutorialBase*> DMPuzzleBBehavior::getTutorials()
{
	return { };
}
