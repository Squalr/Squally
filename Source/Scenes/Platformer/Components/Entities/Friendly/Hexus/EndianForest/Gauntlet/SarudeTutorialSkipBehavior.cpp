#include "SarudeTutorialSkipBehavior.h"

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

const std::string SarudeTutorialSkipBehavior::WinLossTrackIdentifier = "sarude-tutorial";

SarudeTutorialSkipBehavior* SarudeTutorialSkipBehavior::create(GameObject* owner)
{
	SarudeTutorialSkipBehavior* instance = new SarudeTutorialSkipBehavior(owner);

	instance->autorelease();

	return instance;
}

SarudeTutorialSkipBehavior::SarudeTutorialSkipBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1, false, Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_WeAcceptYourChallengeSkip::create())
{
}

SarudeTutorialSkipBehavior::~SarudeTutorialSkipBehavior()
{
}

MinMaxPool* SarudeTutorialSkipBehavior::generateReward()
{
	return HexusPoolSarude::create();
}

std::string SarudeTutorialSkipBehavior::getWinLossSaveKey()
{
	return SarudeTutorialSkipBehavior::WinLossTrackIdentifier;
}

std::string SarudeTutorialSkipBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> SarudeTutorialSkipBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(18, 0.07f,
	{
	});
}

StateOverride* SarudeTutorialSkipBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> SarudeTutorialSkipBehavior::getTutorials()
{
	return { };
}
