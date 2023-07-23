#include "Tier1EFHexusBehavior.h"

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

const std::string Tier1EFHexusBehavior::MapKey = "ef-t1-hexus";

Tier1EFHexusBehavior* Tier1EFHexusBehavior::create(GameObject* owner)
{
	Tier1EFHexusBehavior* instance = new Tier1EFHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier1EFHexusBehavior::Tier1EFHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier1EFHexusBehavior::~Tier1EFHexusBehavior()
{
}

MinMaxPool* Tier1EFHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolEFGeneric::create(properties);
}

std::string Tier1EFHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "bard-hexus"; // Tier1EFHexusBehavior::MapKey;
}

std::string Tier1EFHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameEndianForest;
}

std::vector<CardData*> Tier1EFHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, this->calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
	});
}

StateOverride* Tier1EFHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier1EFHexusBehavior::getTutorials()
{
	return { };
}
