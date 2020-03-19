#include "LianaHexusBehavior.h"

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

const std::string LianaHexusBehavior::MapKey = "liana-hexus";

LianaHexusBehavior* LianaHexusBehavior::create(GameObject* owner)
{
	LianaHexusBehavior* instance = new LianaHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

LianaHexusBehavior::LianaHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

LianaHexusBehavior::~LianaHexusBehavior()
{
}

MinMaxPool* LianaHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string LianaHexusBehavior::getWinLossSaveKey()
{
	return LianaHexusBehavior::MapKey;
}

std::string LianaHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> LianaHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
	});
}

StateOverride* LianaHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> LianaHexusBehavior::getTutorials()
{
	return { };
}
