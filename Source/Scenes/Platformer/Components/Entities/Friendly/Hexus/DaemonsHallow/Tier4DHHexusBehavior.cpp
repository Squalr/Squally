#include "Tier4DHHexusBehavior.h"

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

const std::string Tier4DHHexusBehavior::MapKey = "dh-t4-hexus";

Tier4DHHexusBehavior* Tier4DHHexusBehavior::create(GameObject* owner)
{
	Tier4DHHexusBehavior* instance = new Tier4DHHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier4DHHexusBehavior::Tier4DHHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier4DHHexusBehavior::~Tier4DHHexusBehavior()
{
}

MinMaxPool* Tier4DHHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDHGeneric::create(properties);
}

std::string Tier4DHHexusBehavior::getWinLossSaveKey()
{
	return Tier4DHHexusBehavior::MapKey;
}

std::string Tier4DHHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDaemonsHallow;
}

std::vector<CardData*> Tier4DHHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / DHHexusConfig::MaxEntities;

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

StateOverride* Tier4DHHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier4DHHexusBehavior::getTutorials()
{
	return { };
}
