#include "RobinHexusBehavior.h"

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

const std::string RobinHexusBehavior::MapKey = "robin-hexus";

RobinHexusBehavior* RobinHexusBehavior::create(GameObject* owner)
{
	RobinHexusBehavior* instance = new RobinHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

RobinHexusBehavior::RobinHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

RobinHexusBehavior::~RobinHexusBehavior()
{
}

MinMaxPool* RobinHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string RobinHexusBehavior::getWinLossSaveKey()
{
	return RobinHexusBehavior::MapKey;
}

std::string RobinHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> RobinHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
	});
}

StateOverride* RobinHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> RobinHexusBehavior::getTutorials()
{
	return { };
}
