#include "Tier5BPHexusBehavior.h"

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

const std::string Tier5BPHexusBehavior::MapKey = "bp-t5-hexus";

Tier5BPHexusBehavior* Tier5BPHexusBehavior::create(GameObject* owner)
{
	Tier5BPHexusBehavior* instance = new Tier5BPHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier5BPHexusBehavior::Tier5BPHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier5BPHexusBehavior::~Tier5BPHexusBehavior()
{
}

MinMaxPool* Tier5BPHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolBPGeneric::create(properties);
}

std::string Tier5BPHexusBehavior::getWinLossSaveKey()
{
	return Tier5BPHexusBehavior::MapKey;
}

std::string Tier5BPHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameBallmerPeaks;
}

std::vector<CardData*> Tier5BPHexusBehavior::generateDeck()
{
	const float LocalOrder = 5.0f / BPHexusConfig::MaxEntities;

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

StateOverride* Tier5BPHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier5BPHexusBehavior::getTutorials()
{
	return { };
}
