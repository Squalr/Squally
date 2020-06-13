#include "ThorHexusBehavior.h"

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

const std::string ThorHexusBehavior::MapKey = "thor-hexus";

ThorHexusBehavior* ThorHexusBehavior::create(GameObject* owner)
{
	ThorHexusBehavior* instance = new ThorHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

ThorHexusBehavior::ThorHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

ThorHexusBehavior::~ThorHexusBehavior()
{
}

MinMaxPool* ThorHexusBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string ThorHexusBehavior::getWinLossSaveKey()
{
	return ThorHexusBehavior::MapKey;
}

std::string ThorHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ThorHexusBehavior::generateDeck()
{
	const float LocalOrder = 7.0f / URHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(28, calculateStrength(LocalOrder, URHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		// CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
	});
}

StateOverride* ThorHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> ThorHexusBehavior::getTutorials()
{
	return { };
}
