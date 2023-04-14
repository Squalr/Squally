#include "Tier2URHexusBehavior.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/HexusPools/UnderflowRuins/HexusPoolURGeneric.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/UnderflowRuins/URHexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tier2URHexusBehavior::MapKey = "ur-t2-hexus";

Tier2URHexusBehavior* Tier2URHexusBehavior::create(GameObject* owner)
{
	Tier2URHexusBehavior* instance = new Tier2URHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

Tier2URHexusBehavior::Tier2URHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1)
{
}

Tier2URHexusBehavior::~Tier2URHexusBehavior()
{
}

MinMaxPool* Tier2URHexusBehavior::generateReward()
{
	ValueMap properties = ValueMap();
	return HexusPoolURGeneric::create(properties);
}

std::string Tier2URHexusBehavior::getWinLossSaveKey()
{
	// Backwards compatibility, use old string for save key
	return "hera-hexus"; // Tier2URHexusBehavior::MapKey;
}

std::string Tier2URHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameUnderflowRuins;
}

std::vector<CardData*> Tier2URHexusBehavior::generateDeck()
{
	const float LocalOrder = 2.0f / URHexusConfig::MaxEntities;

	return HexusOpponentData::generateDeck(28, calculateStrength(LocalOrder, URHexusConfig::ZoneOrder),
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],

		// CardList::getInstance()->cardListByName[CardKeys::Mov],
		CardList::getInstance()->cardListByName[CardKeys::Mov],
		// CardList::getInstance()->cardListByName[CardKeys::Flip1],
		CardList::getInstance()->cardListByName[CardKeys::Flip1],
		// CardList::getInstance()->cardListByName[CardKeys::Flip2],
		CardList::getInstance()->cardListByName[CardKeys::Flip2],
		// CardList::getInstance()->cardListByName[CardKeys::Addition],
		CardList::getInstance()->cardListByName[CardKeys::Addition],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		CardList::getInstance()->cardListByName[CardKeys::ShiftLeft],
		// CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		CardList::getInstance()->cardListByName[CardKeys::ShiftRight],
		// CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
		CardList::getInstance()->cardListByName[CardKeys::LogicalOr],
	});
}

StateOverride* Tier2URHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> Tier2URHexusBehavior::getTutorials()
{
	return { };
}
