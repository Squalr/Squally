#include "AraHexusBehavior.h"

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

const std::string AraHexusBehavior::MapKey = "ara-hexus";

AraHexusBehavior* AraHexusBehavior::create(GameObject* owner)
{
	AraHexusBehavior* instance = new AraHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

AraHexusBehavior::AraHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

AraHexusBehavior::~AraHexusBehavior()
{
}

MinMaxPool* AraHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string AraHexusBehavior::getWinLossSaveKey()
{
	return AraHexusBehavior::MapKey;
}

std::string AraHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> AraHexusBehavior::generateDeck()
{
	const float LocalOrder = 7.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, LocalOrder * EFHexusConfig::ZoneOrder,
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

StateOverride* AraHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> AraHexusBehavior::getTutorials()
{
	return { };
}
