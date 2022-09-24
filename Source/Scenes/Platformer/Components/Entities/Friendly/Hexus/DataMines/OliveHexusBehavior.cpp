#include "OliveHexusBehavior.h"

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

const std::string OliveHexusBehavior::MapKey = "olive-hexus";

OliveHexusBehavior* OliveHexusBehavior::create(GameObject* owner)
{
	OliveHexusBehavior* instance = new OliveHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

OliveHexusBehavior::OliveHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

OliveHexusBehavior::~OliveHexusBehavior()
{
}

MinMaxPool* OliveHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string OliveHexusBehavior::getWinLossSaveKey()
{
	return OliveHexusBehavior::MapKey;
}

std::string OliveHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> OliveHexusBehavior::generateDeck()
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

StateOverride* OliveHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> OliveHexusBehavior::getTutorials()
{
	return { };
}
