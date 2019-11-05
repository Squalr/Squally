#include "SarudeTutorialBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPools.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/IAcceptYourChallenge.h"

using namespace cocos2d;

const std::string SarudeTutorialBehavior::WinLossTrackIdentifier = "sarude-tutorial";

SarudeTutorialBehavior* SarudeTutorialBehavior::create(GameObject* owner)
{
	SarudeTutorialBehavior* instance = new SarudeTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

SarudeTutorialBehavior::SarudeTutorialBehavior(GameObject* owner) : super(owner, Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_IAcceptYourChallenge::create())
{
}

SarudeTutorialBehavior::~SarudeTutorialBehavior()
{
}

std::vector<CardData*> SarudeTutorialBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 0.07f,
	{
	});
}

MinMaxPool* SarudeTutorialBehavior::generateReward()
{
	return CardPoolTutorial::create();
}

std::string SarudeTutorialBehavior::getWinLossSaveKey()
{
	return SarudeTutorialBehavior::WinLossTrackIdentifier;
}

std::string SarudeTutorialBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}
