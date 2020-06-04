#include "AngelHexusBehavior.h"

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

const std::string AngelHexusBehavior::MapKey = "angel-hexus";

AngelHexusBehavior* AngelHexusBehavior::create(GameObject* owner)
{
	AngelHexusBehavior* instance = new AngelHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

AngelHexusBehavior::AngelHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

AngelHexusBehavior::~AngelHexusBehavior()
{
}

MinMaxPool* AngelHexusBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string AngelHexusBehavior::getWinLossSaveKey()
{
	return AngelHexusBehavior::MapKey;
}

std::string AngelHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> AngelHexusBehavior::generateDeck()
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

StateOverride* AngelHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> AngelHexusBehavior::getTutorials()
{
	return { };
}
