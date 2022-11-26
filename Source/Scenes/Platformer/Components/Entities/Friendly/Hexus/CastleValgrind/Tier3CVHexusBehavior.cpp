#include "Tier3CVHexusBehavior.h"

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

const std::string Tier3CVHexusBehavior::MapKey = "cv-t3-hexus";

Tier3CVHexusBehavior* Tier3CVHexusBehavior::create(GameObject* owner)
{
	Tier3CVHexusBehavior* instance = new Tier3CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier3CVHexusBehavior::Tier3CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier3CVHexusBehavior::~Tier3CVHexusBehavior()
{
}

MinMaxPool* Tier3CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier3CVHexusBehavior::getWinLossSaveKey()
{
	return Tier3CVHexusBehavior::MapKey;
}

std::string Tier3CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier3CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / CVHexusConfig::MaxEntities;

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

StateOverride* Tier3CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier3CVHexusBehavior::getTutorials()
{
	return { };
}
