#include "Tier6DMHexusBehavior.h"

#include "cocos/base/CCValue.h"

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

const std::string Tier6DMHexusBehavior::MapKey = "dm-t6-hexus";

Tier6DMHexusBehavior* Tier6DMHexusBehavior::create(GameObject* owner)
{
	Tier6DMHexusBehavior* instance = new Tier6DMHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier6DMHexusBehavior::Tier6DMHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier6DMHexusBehavior::~Tier6DMHexusBehavior()
{
}

MinMaxPool* Tier6DMHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolDMGeneric::create(properties);
}

std::string Tier6DMHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "godiva-hexus"; // Tier6DMHexusBehavior::MapKey;
}

std::string Tier6DMHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameDataMines;
}

std::vector<CardData*> Tier6DMHexusBehavior::generateDeck()
{
	const float LocalOrder = 6.0f / DMHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(25, this->calculateStrength(LocalOrder, DMHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Flip2],
		CardList::getInstance()->cardListByName[CardKeys::Flip3],
		// CardList::getInstance()->cardListByName[CardKeys::Flip3],
		// CardList::getInstance()->cardListByName[CardKeys::Flip4],
		// CardList::getInstance()->cardListByName[CardKeys::Flip4],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		CardList::getInstance()->cardListByName[CardKeys::Absorb],
		// CardList::getInstance()->cardListByName[CardKeys::Absorb],
		// CardList::getInstance()->cardListByName[CardKeys::Greed],
		// CardList::getInstance()->cardListByName[CardKeys::Greed],
		// CardList::getInstance()->cardListByName[CardKeys::BonusMoves],
		// CardList::getInstance()->cardListByName[CardKeys::BonusMoves],
		// CardList::getInstance()->cardListByName[CardKeys::Subtraction],
		// CardList::getInstance()->cardListByName[CardKeys::Subtraction],
		// CardList::getInstance()->cardListByName[CardKeys::Kill],
		// CardList::getInstance()->cardListByName[CardKeys::Kill],
		// CardList::getInstance()->cardListByName[CardKeys::Steal],
		// CardList::getInstance()->cardListByName[CardKeys::Steal],
		// CardList::getInstance()->cardListByName[CardKeys::SuddenDeath],
		// CardList::getInstance()->cardListByName[CardKeys::SuddenDeath],
	});
}

StateOverride* Tier6DMHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier6DMHexusBehavior::getTutorials()
{
	return { };
}
