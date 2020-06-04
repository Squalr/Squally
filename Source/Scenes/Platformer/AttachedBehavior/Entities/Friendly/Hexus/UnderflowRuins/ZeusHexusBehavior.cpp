#include "ZeusHexusBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/UnderflowRuins/HexusPoolURGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/UnderflowRuins/URHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ZeusHexusBehavior::MapKey = "zeus-hexus";

ZeusHexusBehavior* ZeusHexusBehavior::create(GameObject* owner)
{
	ZeusHexusBehavior* instance = new ZeusHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

ZeusHexusBehavior::ZeusHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

ZeusHexusBehavior::~ZeusHexusBehavior()
{
}

MinMaxPool* ZeusHexusBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string ZeusHexusBehavior::getWinLossSaveKey()
{
	return ZeusHexusBehavior::MapKey;
}

std::string ZeusHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ZeusHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / URHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * URHexusConfig::ZoneOrder,
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
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* ZeusHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> ZeusHexusBehavior::getTutorials()
{
	return { };
}
