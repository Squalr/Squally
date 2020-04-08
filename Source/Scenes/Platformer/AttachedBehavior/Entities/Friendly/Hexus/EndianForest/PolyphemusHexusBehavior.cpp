#include "PolyphemusHexusBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolEFGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/EFHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PolyphemusHexusBehavior::MapKey = "polyphemus-hexus";

PolyphemusHexusBehavior* PolyphemusHexusBehavior::create(GameObject* owner)
{
	PolyphemusHexusBehavior* instance = new PolyphemusHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

PolyphemusHexusBehavior::PolyphemusHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

PolyphemusHexusBehavior::~PolyphemusHexusBehavior()
{
}

MinMaxPool* PolyphemusHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string PolyphemusHexusBehavior::getWinLossSaveKey()
{
	return PolyphemusHexusBehavior::MapKey;
}

std::string PolyphemusHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> PolyphemusHexusBehavior::generateDeck()
{
	const float LocalOrder = 0.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* PolyphemusHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> PolyphemusHexusBehavior::getTutorials()
{
	return { };
}
