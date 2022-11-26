#include "Tier2CVHexusBehavior.h"

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

const std::string Tier2CVHexusBehavior::MapKey = "cv-t2-hexus";

Tier2CVHexusBehavior* Tier2CVHexusBehavior::create(GameObject* owner)
{
	Tier2CVHexusBehavior* instance = new Tier2CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier2CVHexusBehavior::Tier2CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier2CVHexusBehavior::~Tier2CVHexusBehavior()
{
}

MinMaxPool* Tier2CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier2CVHexusBehavior::getWinLossSaveKey()
{
	return Tier2CVHexusBehavior::MapKey;
}

std::string Tier2CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier2CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 2.0f / CVHexusConfig::MaxEntities;

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

StateOverride* Tier2CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier2CVHexusBehavior::getTutorials()
{
	return { };
}
