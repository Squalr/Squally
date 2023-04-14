#include "Tier8EFHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolEFGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/EndianForest/EFHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier8EFHexusBehavior::MapKey = "ef-t8-hexus";

Tier8EFHexusBehavior* Tier8EFHexusBehavior::create(GameObject* owner)
{
	Tier8EFHexusBehavior* instance = new Tier8EFHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier8EFHexusBehavior::Tier8EFHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier8EFHexusBehavior::~Tier8EFHexusBehavior()
{
}

MinMaxPool* Tier8EFHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolEFGeneric::create(properties);
}

std::string Tier8EFHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "ara-hexus"; // Tier8EFHexusBehavior::MapKey;
}

std::string Tier8EFHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameEndianForest;
}

std::vector<CardData*> Tier8EFHexusBehavior::generateDeck()
{
	const float LocalOrder = 8.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* Tier8EFHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier8EFHexusBehavior::getTutorials()
{
	return { };
}
