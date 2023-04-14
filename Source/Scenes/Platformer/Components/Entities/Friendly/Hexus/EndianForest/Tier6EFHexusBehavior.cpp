#include "Tier6EFHexusBehavior.h"

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

const std::string Tier6EFHexusBehavior::MapKey = "ef-t6-hexus";

Tier6EFHexusBehavior* Tier6EFHexusBehavior::create(GameObject* owner)
{
	Tier6EFHexusBehavior* instance = new Tier6EFHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier6EFHexusBehavior::Tier6EFHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier6EFHexusBehavior::~Tier6EFHexusBehavior()
{
}

MinMaxPool* Tier6EFHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolEFGeneric::create(properties);
}

std::string Tier6EFHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "gramps-hexus"; // Tier6EFHexusBehavior::MapKey;
}

std::string Tier6EFHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameEndianForest;
}

std::vector<CardData*> Tier6EFHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
	});
}

StateOverride* Tier6EFHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier6EFHexusBehavior::getTutorials()
{
	return { };
}
