#include "BancroftHexusBehavior.h"

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

const std::string BancroftHexusBehavior::MapKey = "bancroft-hexus";

BancroftHexusBehavior* BancroftHexusBehavior::create(GameObject* owner)
{
	BancroftHexusBehavior* instance = new BancroftHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

BancroftHexusBehavior::BancroftHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

BancroftHexusBehavior::~BancroftHexusBehavior()
{
}

MinMaxPool* BancroftHexusBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string BancroftHexusBehavior::getWinLossSaveKey()
{
	return BancroftHexusBehavior::MapKey;
}

std::string BancroftHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> BancroftHexusBehavior::generateDeck()
{
	const float LocalOrder = 7.0f / DMHexusConfig::MaxEntities;

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

StateOverride* BancroftHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> BancroftHexusBehavior::getTutorials()
{
	return { };
}
