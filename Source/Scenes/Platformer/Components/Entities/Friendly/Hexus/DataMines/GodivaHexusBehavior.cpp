#include "GodivaHexusBehavior.h"

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

const std::string GodivaHexusBehavior::MapKey = "godiva-hexus";

GodivaHexusBehavior* GodivaHexusBehavior::create(GameObject* owner)
{
	GodivaHexusBehavior* instance = new GodivaHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

GodivaHexusBehavior::GodivaHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

GodivaHexusBehavior::~GodivaHexusBehavior()
{
}

MinMaxPool* GodivaHexusBehavior::generateReward()
{
	return HexusPoolDMGeneric::create();
}

std::string GodivaHexusBehavior::getWinLossSaveKey()
{
	return GodivaHexusBehavior::MapKey;
}

std::string GodivaHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> GodivaHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / DMHexusConfig::MaxEntities;

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

StateOverride* GodivaHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> GodivaHexusBehavior::getTutorials()
{
	return { };
}
