#include "MildredHexusBehavior.h"

#include "Objects/Platformer/ItemPools/HexusPools/DataMines/HexusPoolDMGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/DataMines/DMHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MildredHexusBehavior::MapKey = "mildred-hexus";

MildredHexusBehavior* MildredHexusBehavior::create(GameObject* owner)
{
	MildredHexusBehavior* instance = new MildredHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

MildredHexusBehavior::MildredHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

MildredHexusBehavior::~MildredHexusBehavior()
{
}

MinMaxPool* MildredHexusBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string MildredHexusBehavior::getWinLossSaveKey()
{
	return MildredHexusBehavior::MapKey;
}

std::string MildredHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> MildredHexusBehavior::generateDeck()
{
	const float LocalOrder = 8.0f / DMHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, DMHexusConfig::ZoneOrder),
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

StateOverride* MildredHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> MildredHexusBehavior::getTutorials()
{
	return { };
}
