#include "Tier6CVHexusBehavior.h"

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

const std::string Tier6CVHexusBehavior::MapKey = "cv-t6-hexus";

Tier6CVHexusBehavior* Tier6CVHexusBehavior::create(GameObject* owner)
{
	Tier6CVHexusBehavior* instance = new Tier6CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier6CVHexusBehavior::Tier6CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier6CVHexusBehavior::~Tier6CVHexusBehavior()
{
}

MinMaxPool* Tier6CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier6CVHexusBehavior::getWinLossSaveKey()
{
	return Tier6CVHexusBehavior::MapKey;
}

std::string Tier6CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier6CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / CVHexusConfig::MaxEntities;

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

StateOverride* Tier6CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier6CVHexusBehavior::getTutorials()
{
	return { };
}
