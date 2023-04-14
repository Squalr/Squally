#include "Tier7EFHexusBehavior.h"

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

const std::string Tier7EFHexusBehavior::MapKey = "ef-t7-hexus";

Tier7EFHexusBehavior* Tier7EFHexusBehavior::create(GameObject* owner)
{
	Tier7EFHexusBehavior* instance = new Tier7EFHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier7EFHexusBehavior::Tier7EFHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier7EFHexusBehavior::~Tier7EFHexusBehavior()
{
}

MinMaxPool* Tier7EFHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolEFGeneric::create(properties);
}

std::string Tier7EFHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "matu-hexus"; // Tier7EFHexusBehavior::MapKey;
}

std::string Tier7EFHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameEndianForest;
}

std::vector<CardData*> Tier7EFHexusBehavior::generateDeck()
{
	const float LocalOrder = 7.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, this->calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
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

StateOverride* Tier7EFHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier7EFHexusBehavior::getTutorials()
{
	return { };
}
