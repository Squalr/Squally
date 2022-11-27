#include "Tier2BPHexusBehavior.h"

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

const std::string Tier2BPHexusBehavior::MapKey = "bp-t2-hexus";

Tier2BPHexusBehavior* Tier2BPHexusBehavior::create(GameObject* owner)
{
	Tier2BPHexusBehavior* instance = new Tier2BPHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier2BPHexusBehavior::Tier2BPHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier2BPHexusBehavior::~Tier2BPHexusBehavior()
{
}

MinMaxPool* Tier2BPHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolBPGeneric::create(properties);
}

std::string Tier2BPHexusBehavior::getWinLossSaveKey()
{
	return Tier2BPHexusBehavior::MapKey;
}

std::string Tier2BPHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameBallmerPeaks;
}

std::vector<CardData*> Tier2BPHexusBehavior::generateDeck()
{
	const float LocalOrder = 2.0f / BPHexusConfig::MaxEntities;

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

StateOverride* Tier2BPHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier2BPHexusBehavior::getTutorials()
{
	return { };
}
