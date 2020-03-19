#include "TobenHexusBehavior.h"

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

const std::string TobenHexusBehavior::MapKey = "toben-hexus";

TobenHexusBehavior* TobenHexusBehavior::create(GameObject* owner)
{
	TobenHexusBehavior* instance = new TobenHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

TobenHexusBehavior::TobenHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

TobenHexusBehavior::~TobenHexusBehavior()
{
}

MinMaxPool* TobenHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string TobenHexusBehavior::getWinLossSaveKey()
{
	return TobenHexusBehavior::MapKey;
}

std::string TobenHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> TobenHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
	});
}

StateOverride* TobenHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> TobenHexusBehavior::getTutorials()
{
	return { };
}
