#include "MatuHexusBehavior.h"

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

const std::string MatuHexusBehavior::MapKeyAttachedBehavior = "matu-hexus";

MatuHexusBehavior* MatuHexusBehavior::create(GameObject* owner)
{
	MatuHexusBehavior* instance = new MatuHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

MatuHexusBehavior::MatuHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

MatuHexusBehavior::~MatuHexusBehavior()
{
}

MinMaxPool* MatuHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string MatuHexusBehavior::getWinLossSaveKey()
{
	return MatuHexusBehavior::MapKeyAttachedBehavior;
}

std::string MatuHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> MatuHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
	});
}

StateOverride* MatuHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> MatuHexusBehavior::getTutorials()
{
	return { };
}
