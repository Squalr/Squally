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

const std::string BlackbeardHexusBehavior::MapKey = "blackbeard-hexus";

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
	return BlackbeardHexusBehavior::MapKey;
}

std::string BlackbeardHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> BlackbeardHexusBehavior::generateDeck()
{
	const float LocalOrder = 0.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
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
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
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
