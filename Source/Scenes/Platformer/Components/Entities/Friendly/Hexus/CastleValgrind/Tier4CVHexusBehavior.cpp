#include "Tier4CVHexusBehavior.h"

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

const std::string Tier4CVHexusBehavior::MapKey = "cv-t4-hexus";

Tier4CVHexusBehavior* Tier4CVHexusBehavior::create(GameObject* owner)
{
	Tier4CVHexusBehavior* instance = new Tier4CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier4CVHexusBehavior::Tier4CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier4CVHexusBehavior::~Tier4CVHexusBehavior()
{
}

MinMaxPool* Tier4CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier4CVHexusBehavior::getWinLossSaveKey()
{
	return Tier4CVHexusBehavior::MapKey;
}

std::string Tier4CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier4CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / CVHexusConfig::MaxEntities;

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

StateOverride* Tier4CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier4CVHexusBehavior::getTutorials()
{
	return { };
}
