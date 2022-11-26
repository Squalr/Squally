#include "Tier1CVHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/CastleValgrind/HexusPoolCVGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/CastleValgrind/CVHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier1CVHexusBehavior::MapKey = "cv-t1-hexus";

Tier1CVHexusBehavior* Tier1CVHexusBehavior::create(GameObject* owner)
{
	Tier1CVHexusBehavior* instance = new Tier1CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier1CVHexusBehavior::Tier1CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier1CVHexusBehavior::~Tier1CVHexusBehavior()
{
}

MinMaxPool* Tier1CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier1CVHexusBehavior::getWinLossSaveKey()
{
	return Tier1CVHexusBehavior::MapKey;
}

std::string Tier1CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier1CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / CVHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, CVHexusConfig::ZoneOrder),
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

StateOverride* Tier1CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier1CVHexusBehavior::getTutorials()
{
	return { };
}
