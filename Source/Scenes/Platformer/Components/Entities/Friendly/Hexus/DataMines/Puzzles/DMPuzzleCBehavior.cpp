#include "DMPuzzleCBehavior.h"

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

const std::string DMPuzzleCBehavior::MapKey = "dm-puzzle-C";

DMPuzzleCBehavior* DMPuzzleCBehavior::create(GameObject* owner)
{
	DMPuzzleCBehavior* instance = new DMPuzzleCBehavior(owner);

	instance->autorelease();

	return instance;
}

DMPuzzleCBehavior::DMPuzzleCBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

DMPuzzleCBehavior::~DMPuzzleCBehavior()
{
}

MinMaxPool* DMPuzzleCBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string DMPuzzleCBehavior::getWinLossSaveKey()
{
	return DMPuzzleCBehavior::MapKey;
}

std::string DMPuzzleCBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> DMPuzzleCBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* DMPuzzleCBehavior::getStateOverride()
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
			CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
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

std::vector<TutorialBase*> DMPuzzleCBehavior::getTutorials()
{
	return { };
}
