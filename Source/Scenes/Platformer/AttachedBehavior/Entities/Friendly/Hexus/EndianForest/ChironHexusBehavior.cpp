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

const std::string ChironHexusBehavior::WinLossTrackIdentifier = "chiron-hexus";

ChironHexusBehavior* ChironHexusBehavior::create(GameObject* owner)
{
	ChironHexusBehavior* instance = new ChironHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

ChironHexusBehavior::ChironHexusBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1, Strings::Platformer_Dialogue_Hexus_IAcceptYourChallenge::create())
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
	return ChironHexusBehavior::WinLossTrackIdentifier;
}

std::string ChironHexusBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> ChironHexusBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 0.07f,
	{
		// CardList::getInstance()->cardListByName[CardKeys::Decimal0],
	});
}

StateOverride* ChironHexusBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> ChironHexusBehavior::getTutorials()
{
	return { MarcelTutorialIntroSequence::create(), MarcelTutorialClaimVictory::create() };
}
