#include "RalstonHexusBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/DataMines/HexusPoolDMGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/DataMines/DMHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RalstonHexusBehavior::MapKey = "ralston-hexus";

RalstonHexusBehavior* RalstonHexusBehavior::create(GameObject* owner)
{
	RalstonHexusBehavior* instance = new RalstonHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

RalstonHexusBehavior::RalstonHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

RalstonHexusBehavior::~RalstonHexusBehavior()
{
}

MinMaxPool* RalstonHexusBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string RalstonHexusBehavior::getWinLossSaveKey()
{
	return RalstonHexusBehavior::MapKey;
}

std::string RalstonHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> RalstonHexusBehavior::generateDeck()
{
	const float LocalOrder = 8.0f / DMHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, DMHexusConfig::ZoneOrder),
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

StateOverride* RalstonHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> RalstonHexusBehavior::getTutorials()
{
	return { };
}
