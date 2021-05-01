#include "ChironHexusBehavior.h"

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

const std::string ChironHexusBehavior::MapKey = "chiron-hexus";

ChironHexusBehavior* ChironHexusBehavior::create(GameObject* owner)
{
	ChironHexusBehavior* instance = new ChironHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

ChironHexusBehavior::ChironHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

ChironHexusBehavior::~ChironHexusBehavior()
{
}

MinMaxPool* ChironHexusBehavior::generateReward()
{
	return HexusPoolEFGeneric::create();
}

std::string ChironHexusBehavior::getWinLossSaveKey()
{
	return ChironHexusBehavior::MapKey;
}

std::string ChironHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ChironHexusBehavior::generateDeck()
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

StateOverride* ChironHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> ChironHexusBehavior::getTutorials()
{
	return { };
}
