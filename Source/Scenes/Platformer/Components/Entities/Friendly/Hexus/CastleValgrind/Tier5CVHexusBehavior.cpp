#include "Tier5CVHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/CastleValgrind/HexusPoolCVGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/CastleValgrind/CVHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier5CVHexusBehavior::MapKey = "cv-t5-hexus";

Tier5CVHexusBehavior* Tier5CVHexusBehavior::create(GameObject* owner)
{
	Tier5CVHexusBehavior* instance = new Tier5CVHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier5CVHexusBehavior::Tier5CVHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier5CVHexusBehavior::~Tier5CVHexusBehavior()
{
}

MinMaxPool* Tier5CVHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolCVGeneric::create(properties);
}

std::string Tier5CVHexusBehavior::getWinLossSaveKey()
{
	return Tier5CVHexusBehavior::MapKey;
}

std::string Tier5CVHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> Tier5CVHexusBehavior::generateDeck()
{
	const float LocalOrder = 5.0f / CVHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(28, this->calculateStrength(LocalOrder, CVHexusConfig::ZoneOrder),
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
		// CardList::getInstance()->cardListByName[CardKeys::Flip3],
		// CardList::getInstance()->cardListByName[CardKeys::Flip3],
		// CardList::getInstance()->cardListByName[CardKeys::Flip4],
		// CardList::getInstance()->cardListByName[CardKeys::Flip4],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeftCircular],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRightCircular],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalXor],
		CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalAnd],
		CardList::getInstance()->cardListByName[CardKeys::Push],
		// CardList::getInstance()->cardListByName[CardKeys::Push],
		CardList::getInstance()->cardListByName[CardKeys::Pop],
		// CardList::getInstance()->cardListByName[CardKeys::Pop],
		CardList::getInstance()->cardListByName[CardKeys::Absorb],
		// CardList::getInstance()->cardListByName[CardKeys::Absorb],
		CardList::getInstance()->cardListByName[CardKeys::Greed],
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
		CardList::getInstance()->cardListByName[CardKeys::Inverse],
		// CardList::getInstance()->cardListByName[CardKeys::Inverse],
		// CardList::getInstance()->cardListByName[CardKeys::ReturnToHand],
		// CardList::getInstance()->cardListByName[CardKeys::ReturnToHand],
		CardList::getInstance()->cardListByName[CardKeys::Clear],
		// CardList::getInstance()->cardListByName[CardKeys::Clear],
	});
}

StateOverride* Tier5CVHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier5CVHexusBehavior::getTutorials()
{
	return { };
}
