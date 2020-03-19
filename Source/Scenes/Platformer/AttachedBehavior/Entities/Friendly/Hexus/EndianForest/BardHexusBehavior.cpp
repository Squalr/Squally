#include "BardHexusBehavior.h"

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

const std::string BardHexusBehavior::MapKey = "bard-hexus";

BardHexusBehavior* BardHexusBehavior::create(GameObject* owner)
{
	BardHexusBehavior* instance = new BardHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

BardHexusBehavior::BardHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

BardHexusBehavior::~BardHexusBehavior()
{
}

MinMaxPool* BardHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string BardHexusBehavior::getWinLossSaveKey()
{
	return BardHexusBehavior::MapKey;
}

std::string BardHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> BardHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
	});
}

StateOverride* BardHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> BardHexusBehavior::getTutorials()
{
	return { };
}
