#include "Tier3LCHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/LambdaCrypts/HexusPoolLCGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/LambdaCrypts/LCHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier3LCHexusBehavior::MapKey = "lc-t3-hexus";

Tier3LCHexusBehavior* Tier3LCHexusBehavior::create(GameObject* owner)
{
	Tier3LCHexusBehavior* instance = new Tier3LCHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier3LCHexusBehavior::Tier3LCHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier3LCHexusBehavior::~Tier3LCHexusBehavior()
{
}

MinMaxPool* Tier3LCHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string Tier3LCHexusBehavior::getWinLossSaveKey()
{
	return Tier3LCHexusBehavior::MapKey;
}

std::string Tier3LCHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> Tier3LCHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / LCHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, LCHexusConfig::ZoneOrder),
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

StateOverride* Tier3LCHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier3LCHexusBehavior::getTutorials()
{
	return { };
}
