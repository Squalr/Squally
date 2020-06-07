#include "LycanHexusBehavior.h"

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

const std::string LycanHexusBehavior::MapKey = "lycan-hexus";

LycanHexusBehavior* LycanHexusBehavior::create(GameObject* owner)
{
	LycanHexusBehavior* instance = new LycanHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

LycanHexusBehavior::LycanHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

LycanHexusBehavior::~LycanHexusBehavior()
{
}

MinMaxPool* LycanHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string LycanHexusBehavior::getWinLossSaveKey()
{
	return LycanHexusBehavior::MapKey;
}

std::string LycanHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> LycanHexusBehavior::generateDeck()
{
	const float LocalOrder = 3.0f / EFHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, EFHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
	});
}

StateOverride* LycanHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> LycanHexusBehavior::getTutorials()
{
	return { };
}
