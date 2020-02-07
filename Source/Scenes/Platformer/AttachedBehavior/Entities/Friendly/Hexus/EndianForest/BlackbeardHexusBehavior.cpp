#include "BlackbeardHexusBehavior.h"

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

const std::string BlackbeardHexusBehavior::MapKeyAttachedBehavior = "blackbeard-hexus";

BlackbeardHexusBehavior* BlackbeardHexusBehavior::create(GameObject* owner)
{
	BlackbeardHexusBehavior* instance = new BlackbeardHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

BlackbeardHexusBehavior::BlackbeardHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

BlackbeardHexusBehavior::~BlackbeardHexusBehavior()
{
}

MinMaxPool* BlackbeardHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string BlackbeardHexusBehavior::getWinLossSaveKey()
{
	return BlackbeardHexusBehavior::MapKeyAttachedBehavior;
}

std::string BlackbeardHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> BlackbeardHexusBehavior::generateDeck()
{
	const float LocalOrder = 8.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
	});
}

StateOverride* BlackbeardHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> BlackbeardHexusBehavior::getTutorials()
{
	return { };
}
