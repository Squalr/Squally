#include "MarcelHexusBehavior.h"

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

const std::string MarcelHexusBehavior::MapKey = "marcel-hexus";

MarcelHexusBehavior* MarcelHexusBehavior::create(GameObject* owner)
{
	MarcelHexusBehavior* instance = new MarcelHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

MarcelHexusBehavior::MarcelHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

MarcelHexusBehavior::~MarcelHexusBehavior()
{
}

MinMaxPool* MarcelHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string MarcelHexusBehavior::getWinLossSaveKey()
{
	return MarcelHexusBehavior::MapKey;
}

std::string MarcelHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> MarcelHexusBehavior::generateDeck()
{
	const float LocalOrder = 0.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* MarcelHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> MarcelHexusBehavior::getTutorials()
{
	return { };
}
