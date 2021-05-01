#include "ElrielHexusBehavior.h"

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

const std::string ElrielHexusBehavior::MapKey = "elriel-hexus";

ElrielHexusBehavior* ElrielHexusBehavior::create(GameObject* owner)
{
	ElrielHexusBehavior* instance = new ElrielHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

ElrielHexusBehavior::ElrielHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

ElrielHexusBehavior::~ElrielHexusBehavior()
{
}

MinMaxPool* ElrielHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string ElrielHexusBehavior::getWinLossSaveKey()
{
	return ElrielHexusBehavior::MapKey;
}

std::string ElrielHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ElrielHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / EFHexusConfig::MaxEntities;

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
		CardList::getInstance()->cardListByName[CardKeys::Addition],
	});
}

StateOverride* ElrielHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> ElrielHexusBehavior::getTutorials()
{
	return { };
}
