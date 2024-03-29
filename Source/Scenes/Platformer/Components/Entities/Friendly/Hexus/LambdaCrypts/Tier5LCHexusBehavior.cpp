#include "Tier5LCHexusBehavior.h"

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

const std::string Tier5LCHexusBehavior::MapKey = "lc-t5-hexus";

Tier5LCHexusBehavior* Tier5LCHexusBehavior::create(GameObject* owner)
{
	Tier5LCHexusBehavior* instance = new Tier5LCHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier5LCHexusBehavior::Tier5LCHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier5LCHexusBehavior::~Tier5LCHexusBehavior()
{
}

MinMaxPool* Tier5LCHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolLCGeneric::create(properties);
}

std::string Tier5LCHexusBehavior::getWinLossSaveKey()
{
	return Tier5LCHexusBehavior::MapKey;
}

std::string Tier5LCHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameLambdaCrypts;
}

std::vector<CardData*> Tier5LCHexusBehavior::generateDeck()
{
	const float LocalOrder = 5.0f / LCHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(32, this->calculateStrength(LocalOrder, LCHexusConfig::ZoneOrder),
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
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		// CardList::getInstance()->cardListByName[CardKeys::Push],
		// CardList::getInstance()->cardListByName[CardKeys::Push],
		CardList::getInstance()->cardListByName[CardKeys::Pop],
		// CardList::getInstance()->cardListByName[CardKeys::Pop],
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
		CardList::getInstance()->cardListByName[CardKeys::Steal],
		// CardList::getInstance()->cardListByName[CardKeys::Steal],
		// CardList::getInstance()->cardListByName[CardKeys::SuddenDeath],
		// CardList::getInstance()->cardListByName[CardKeys::SuddenDeath],
		// CardList::getInstance()->cardListByName[CardKeys::Inverse],
		// CardList::getInstance()->cardListByName[CardKeys::Inverse],
		CardList::getInstance()->cardListByName[CardKeys::ReturnToHand],
		// CardList::getInstance()->cardListByName[CardKeys::ReturnToHand],
		// CardList::getInstance()->cardListByName[CardKeys::Clear],
		// CardList::getInstance()->cardListByName[CardKeys::Clear],
	});
}

StateOverride* Tier5LCHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier5LCHexusBehavior::getTutorials()
{
	return { };
}
