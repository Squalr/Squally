#include "Tier1DHHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/DaemonsHallow/HexusPoolDHGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/DaemonsHallow/DHHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier1DHHexusBehavior::MapKey = "dh-t1-hexus";

Tier1DHHexusBehavior* Tier1DHHexusBehavior::create(GameObject* owner)
{
	Tier1DHHexusBehavior* instance = new Tier1DHHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier1DHHexusBehavior::Tier1DHHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier1DHHexusBehavior::~Tier1DHHexusBehavior()
{
}

MinMaxPool* Tier1DHHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string Tier1DHHexusBehavior::getWinLossSaveKey()
{
	return Tier1DHHexusBehavior::MapKey;
}

std::string Tier1DHHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> Tier1DHHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / DHHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, DHHexusConfig::ZoneOrder),
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

StateOverride* Tier1DHHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier1DHHexusBehavior::getTutorials()
{
	return { };
}
