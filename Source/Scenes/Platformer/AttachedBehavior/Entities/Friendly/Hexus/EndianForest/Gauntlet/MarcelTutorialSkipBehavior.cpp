#include "MarcelTutorialSkipBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/HexusPools/HexusPoolMarcel.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/IAcceptYourChallengeSkip.h"

using namespace cocos2d;

const std::string MarcelTutorialSkipBehavior::WinLossTrackIdentifier = "marcel-tutorial";

MarcelTutorialSkipBehavior* MarcelTutorialSkipBehavior::create(GameObject* owner)
{
	MarcelTutorialSkipBehavior* instance = new MarcelTutorialSkipBehavior(owner);

	instance->autorelease();

	return instance;
}

MarcelTutorialSkipBehavior::MarcelTutorialSkipBehavior(GameObject* owner) : super(owner, SoundResources::Platformer_Entities_Generic_ChatterShort1, Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_IAcceptYourChallengeSkip::create())
{
}

MarcelTutorialSkipBehavior::~MarcelTutorialSkipBehavior()
{
}

MinMaxPool* MarcelTutorialSkipBehavior::generateReward()
{
	return HexusPoolMarcel::create();
}

std::string MarcelTutorialSkipBehavior::getWinLossSaveKey()
{
	return MarcelTutorialSkipBehavior::WinLossTrackIdentifier;
}

std::string MarcelTutorialSkipBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> MarcelTutorialSkipBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(18, 0.07f,
	{
	});
}

StateOverride* MarcelTutorialSkipBehavior::getStateOverride()
{
	return nullptr;
}

std::vector<TutorialBase*> MarcelTutorialSkipBehavior::getTutorials()
{
	return { };
}
