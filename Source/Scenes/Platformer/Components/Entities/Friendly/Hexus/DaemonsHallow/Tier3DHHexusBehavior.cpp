#include "Tier3DHHexusBehavior.h"

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

const std::string Tier3DHHexusBehavior::MapKey = "dh-t3-hexus";

Tier3DHHexusBehavior* Tier3DHHexusBehavior::create(GameObject* owner)
{
	Tier3DHHexusBehavior* instance = new Tier3DHHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier3DHHexusBehavior::Tier3DHHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier3DHHexusBehavior::~Tier3DHHexusBehavior()
{
}

MinMaxPool* Tier3DHHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string Tier3DHHexusBehavior::getWinLossSaveKey()
{
	return Tier3DHHexusBehavior::MapKey;
}

std::string Tier3DHHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> Tier3DHHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / DHHexusConfig::MaxEntities;

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

StateOverride* Tier3DHHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier3DHHexusBehavior::getTutorials()
{
	return { };
}
