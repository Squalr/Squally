#include "AjaxHexusBehavior.h"

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

const std::string AjaxHexusBehavior::MapKey = "ajax-hexus";

AjaxHexusBehavior* AjaxHexusBehavior::create(GameObject* owner)
{
	AjaxHexusBehavior* instance = new AjaxHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

AjaxHexusBehavior::AjaxHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

AjaxHexusBehavior::~AjaxHexusBehavior()
{
}

MinMaxPool* AjaxHexusBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string AjaxHexusBehavior::getWinLossSaveKey()
{
	return AjaxHexusBehavior::MapKey;
}

std::string AjaxHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> AjaxHexusBehavior::generateDeck()
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

StateOverride* AjaxHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> AjaxHexusBehavior::getTutorials()
{
	return { };
}
