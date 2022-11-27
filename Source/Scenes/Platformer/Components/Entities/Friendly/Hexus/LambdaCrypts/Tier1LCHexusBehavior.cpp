#include "Tier1LCHexusBehavior.h"

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

const std::string Tier1LCHexusBehavior::MapKey = "lc-t1-hexus";

Tier1LCHexusBehavior* Tier1LCHexusBehavior::create(GameObject* owner)
{
	Tier1LCHexusBehavior* instance = new Tier1LCHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier1LCHexusBehavior::Tier1LCHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier1LCHexusBehavior::~Tier1LCHexusBehavior()
{
}

MinMaxPool* Tier1LCHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string Tier1LCHexusBehavior::getWinLossSaveKey()
{
	return Tier1LCHexusBehavior::MapKey;
}

std::string Tier1LCHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> Tier1LCHexusBehavior::generateDeck()
{
	const float LocalOrder = 1.0f / LCHexusConfig::MaxEntities;

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

StateOverride* Tier1LCHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier1LCHexusBehavior::getTutorials()
{
	return { };
}
