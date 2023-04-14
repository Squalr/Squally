#include "Tier2EFHexusBehavior.h"

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

const std::string Tier2EFHexusBehavior::MapKey = "ef-t2-hexus";

Tier2EFHexusBehavior* Tier2EFHexusBehavior::create(GameObject* owner)
{
	Tier2EFHexusBehavior* instance = new Tier2EFHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier2EFHexusBehavior::Tier2EFHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier2EFHexusBehavior::~Tier2EFHexusBehavior()
{
}

MinMaxPool* Tier2EFHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolEFGeneric::create(properties);
}

std::string Tier2EFHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "chiron-hexus"; // Tier2EFHexusBehavior::MapKey;
}

std::string Tier2EFHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameEndianForest;
}

std::vector<CardData*> Tier2EFHexusBehavior::generateDeck()
{
	const float LocalOrder = 2.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
	});
}

StateOverride* Tier2EFHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier2EFHexusBehavior::getTutorials()
{
	return { };
}
