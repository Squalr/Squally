#include "Tier4BPHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/BallmerPeaks/HexusPoolBPGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/BallmerPeaks/BPHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier4BPHexusBehavior::MapKey = "bp-t4-hexus";

Tier4BPHexusBehavior* Tier4BPHexusBehavior::create(GameObject* owner)
{
	Tier4BPHexusBehavior* instance = new Tier4BPHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier4BPHexusBehavior::Tier4BPHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier4BPHexusBehavior::~Tier4BPHexusBehavior()
{
}

MinMaxPool* Tier4BPHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolBPGeneric::create(properties);
}

std::string Tier4BPHexusBehavior::getWinLossSaveKey()
{
	return Tier4BPHexusBehavior::MapKey;
}

std::string Tier4BPHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameBallmerPeaks;
}

std::vector<CardData*> Tier4BPHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / BPHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, BPHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* Tier4BPHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier4BPHexusBehavior::getTutorials()
{
	return { };
}
