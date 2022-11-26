#include "CVPuzzleGBehavior.h"

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

const std::string CVPuzzleGBehavior::MapKey = "cv-puzzle-G";

CVPuzzleGBehavior* CVPuzzleGBehavior::create(GameObject* owner)
{
	CVPuzzleGBehavior* instance = new CVPuzzleGBehavior(owner);

	instance->autorelease();

	return instance;
}

CVPuzzleGBehavior::CVPuzzleGBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort2, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

CVPuzzleGBehavior::~CVPuzzleGBehavior()
{
}

MinMaxPool* CVPuzzleGBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string CVPuzzleGBehavior::getWinLossSaveKey()
{
	return CVPuzzleGBehavior::MapKey;
}

std::string CVPuzzleGBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> CVPuzzleGBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 1.0f,
	{
	});
}

StateOverride* CVPuzzleGBehavior::getStateOverride()
{
	return StateOverride::create(
		// Player losses
		1,
		// Enemy losses
		1,
		// Player's turn
		false,
		// Player passed
		false,
		// Enemy passed
		false,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Enemy graveyard
		std::vector<CardData*>
		{
			
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Pop),
			CardList::getInstance()->cardListByName.at(CardKeys::Clear),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal10),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
		}
	);
}

std::vector<TutorialBase*> CVPuzzleGBehavior::getTutorials()
{
	return { };
}
