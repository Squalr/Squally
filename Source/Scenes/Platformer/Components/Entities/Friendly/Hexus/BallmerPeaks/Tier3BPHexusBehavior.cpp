#include "Tier3BPHexusBehavior.h"

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

const std::string Tier3BPHexusBehavior::MapKey = "bp-t3-hexus";

Tier3BPHexusBehavior* Tier3BPHexusBehavior::create(GameObject* owner)
{
	Tier3BPHexusBehavior* instance = new Tier3BPHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier3BPHexusBehavior::Tier3BPHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier3BPHexusBehavior::~Tier3BPHexusBehavior()
{
}

MinMaxPool* Tier3BPHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolBPGeneric::create(properties);
}

std::string Tier3BPHexusBehavior::getWinLossSaveKey()
{
	return Tier3BPHexusBehavior::MapKey;
}

std::string Tier3BPHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameBallmerPeaks;
}

std::vector<CardData*> Tier3BPHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / BPHexusConfig::MaxEntities;

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

StateOverride* Tier3BPHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier3BPHexusBehavior::getTutorials()
{
	return { };
}
