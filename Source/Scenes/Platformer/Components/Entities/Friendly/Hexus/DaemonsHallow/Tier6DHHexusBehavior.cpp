#include "Tier6DHHexusBehavior.h"

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

const std::string Tier6DHHexusBehavior::MapKey = "dh-t6-hexus";

Tier6DHHexusBehavior* Tier6DHHexusBehavior::create(GameObject* owner)
{
	Tier6DHHexusBehavior* instance = new Tier6DHHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier6DHHexusBehavior::Tier6DHHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier6DHHexusBehavior::~Tier6DHHexusBehavior()
{
}

MinMaxPool* Tier6DHHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string Tier6DHHexusBehavior::getWinLossSaveKey()
{
	return Tier6DHHexusBehavior::MapKey;
}

std::string Tier6DHHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> Tier6DHHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / DHHexusConfig::MaxEntities;

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

StateOverride* Tier6DHHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier6DHHexusBehavior::getTutorials()
{
	return { };
}
