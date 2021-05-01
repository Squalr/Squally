#include "SarudeTutorialBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/HexusPools/EndianForest/HexusPoolSarude.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SarudeTutorialBehavior::WinLossTrackIdentifier = "sarude-tutorial";

SarudeTutorialBehavior* SarudeTutorialBehavior::create(GameObject* owner)
{
	SarudeTutorialBehavior* instance = new SarudeTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

SarudeTutorialBehavior::SarudeTutorialBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1, false, Strings::Platformer_Dialogue_Hexus_WeAcceptYourChallenge::create())
{
}

SarudeTutorialBehavior::~SarudeTutorialBehavior()
{
}

MinMaxPool* SarudeTutorialBehavior::generateReward()
{
	return HexusPoolSarude::create();
}

std::string SarudeTutorialBehavior::getWinLossSaveKey()
{
	return SarudeTutorialBehavior::WinLossTrackIdentifier;
}

std::string SarudeTutorialBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> SarudeTutorialBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(18, 0.07f,
	{
		// CardList::getInstance()->cardListByName[CardKeys::Decimal0],
	});
}

StateOverride* SarudeTutorialBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> SarudeTutorialBehavior::getTutorials()
{
	return { SarudeTutorialIntroSequence::create(), SarudeTutorialClaimVictory::create() };
}
