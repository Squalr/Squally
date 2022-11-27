#include "Tier2DHHexusBehavior.h"

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

const std::string Tier2DHHexusBehavior::MapKey = "dh-t2-hexus";

Tier2DHHexusBehavior* Tier2DHHexusBehavior::create(GameObject* owner)
{
	Tier2DHHexusBehavior* instance = new Tier2DHHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier2DHHexusBehavior::Tier2DHHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier2DHHexusBehavior::~Tier2DHHexusBehavior()
{
}

MinMaxPool* Tier2DHHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string Tier2DHHexusBehavior::getWinLossSaveKey()
{
	return Tier2DHHexusBehavior::MapKey;
}

std::string Tier2DHHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> Tier2DHHexusBehavior::generateDeck()
{
	const float LocalOrder = 2.0f / DHHexusConfig::MaxEntities;

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

StateOverride* Tier2DHHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier2DHHexusBehavior::getTutorials()
{
	return { };
}
