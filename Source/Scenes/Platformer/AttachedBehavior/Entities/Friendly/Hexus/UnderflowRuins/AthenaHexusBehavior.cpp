#include "AthenaHexusBehavior.h"

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

const std::string AthenaHexusBehavior::MapKey = "athena-hexus";

AthenaHexusBehavior* AthenaHexusBehavior::create(GameObject* owner)
{
	AthenaHexusBehavior* instance = new AthenaHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

AthenaHexusBehavior::AthenaHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

AthenaHexusBehavior::~AthenaHexusBehavior()
{
}

MinMaxPool* AthenaHexusBehavior::generateReward()
{
	return HexusPoolURGeneric::create();
}

std::string AthenaHexusBehavior::getWinLossSaveKey()
{
	return AthenaHexusBehavior::MapKey;
}

std::string AthenaHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> AthenaHexusBehavior::generateDeck()
{
	const float LocalOrder = 5.0f / URHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(28, calculateStrength(LocalOrder, URHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
	});
}

StateOverride* AthenaHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> AthenaHexusBehavior::getTutorials()
{
	return { };
}
