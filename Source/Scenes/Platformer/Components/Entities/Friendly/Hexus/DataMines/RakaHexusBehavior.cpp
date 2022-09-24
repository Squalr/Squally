#include "RakaHexusBehavior.h"

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

const std::string RakaHexusBehavior::MapKey = "raka-hexus";

RakaHexusBehavior* RakaHexusBehavior::create(GameObject* owner)
{
	RakaHexusBehavior* instance = new RakaHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

RakaHexusBehavior::RakaHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

RakaHexusBehavior::~RakaHexusBehavior()
{
}

MinMaxPool* RakaHexusBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string RakaHexusBehavior::getWinLossSaveKey()
{
	return RakaHexusBehavior::MapKey;
}

std::string RakaHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> RakaHexusBehavior::generateDeck()
{
	const float LocalOrder = 4.0f / DMHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, calculateStrength(LocalOrder, DMHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
	});
}

StateOverride* RakaHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> RakaHexusBehavior::getTutorials()
{
	return { };
}
