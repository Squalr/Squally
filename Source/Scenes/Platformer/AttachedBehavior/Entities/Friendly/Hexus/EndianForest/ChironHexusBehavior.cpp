#include "ChironHexusBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolMarcel.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChironHexusBehavior::MapKeyAttachedBehavior = "chiron-hexus";

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
	return HexusPoolMarcel::create();
}

std::string ChironHexusBehavior::getWinLossSaveKey()
{
	return ChironHexusBehavior::MapKeyAttachedBehavior;
}

std::string ChironHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ChironHexusBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 0.08f,
	{
		CardList::getInstance()->cardListByName[CardKeys::Binary0],
		CardList::getInstance()->cardListByName[CardKeys::Decimal0],
		CardList::getInstance()->cardListByName[CardKeys::Hex0],
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
