#include "MarcelTutorialBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPools.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/IAcceptYourChallenge.h"

using namespace cocos2d;

const std::string MarcelTutorialBehavior::WinLossTrackIdentifier = "marcel-tutorial";

MarcelTutorialBehavior* MarcelTutorialBehavior::create(GameObject* owner)
{
	MarcelTutorialBehavior* instance = new MarcelTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

MarcelTutorialBehavior::MarcelTutorialBehavior(GameObject* owner) : super(owner, Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_IAcceptYourChallenge::create())
{
}

MarcelTutorialBehavior::~MarcelTutorialBehavior()
{
}

MinMaxPool* MarcelTutorialBehavior::generateReward()
{
	return CardPoolTutorial::create();
}

std::string MarcelTutorialBehavior::getWinLossSaveKey()
{
	return MarcelTutorialBehavior::WinLossTrackIdentifier;
}

std::string MarcelTutorialBehavior::getBackgroundResource()
{
	return HexusResources::Menus_HexusFrameCastleValgrind;
}

std::vector<CardData*> MarcelTutorialBehavior::generateDeck()
{
	return HexusOpponentData::generateDeck(25, 0.07f,
	{
	});
}

StateOverride* MarcelTutorialBehavior::getStateOverride()
{
	return nullptr;
}
