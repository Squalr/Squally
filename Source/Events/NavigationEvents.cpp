#include "NavigationEvents.h"

#include "cocos/2d/CCScene.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/GlobalDirector.h"

using namespace cocos2d;

const std::string NavigationEvents::EventNavigateTitle = "EVENT_NAVIGATE_TITLE";
const std::string NavigationEvents::EventNavigateLoadingScreen = "EVENT_NAVIGATE_LOADING_SCREEN";
const std::string NavigationEvents::EventNavigateMap = "EVENT_NAVIGATE_MAP";
const std::string NavigationEvents::EventNavigateSaveSelect = "EVENT_NAVIGATE_SAVE_SELECT";
const std::string NavigationEvents::EventNavigateMinigames = "EVENT_NAVIGATE_MINIGAMES";
const std::string NavigationEvents::EventNavigateOptions = "EVENT_NAVIGATE_OPTIONS";
const std::string NavigationEvents::EventNavigateWorldMap = "EVENT_NAVIGATE_WORLD_MAP";
const std::string NavigationEvents::EventNavigateHexus = "EVENT_NAVIGATE_HEXUS";
const std::string NavigationEvents::EventNavigateHexusPuzzles = "EVENT_NAVIGATE_HEXUS_PUZZLES";
const std::string NavigationEvents::EventNavigateHexusRewards = "EVENT_NAVIGATE_HEXUS_REWARDS";
const std::string NavigationEvents::EventNavigateHexusDeckManagement = "EVENT_NAVIGATE_HEXUS_DECK_MANAGEMENT";
const std::string NavigationEvents::EventNavigateHexusShop = "EVENT_NAVIGATE_HEXUS_SHOP";
const std::string NavigationEvents::EventNavigateHexusChapterSelect = "EVENT_NAVIGATE_HEXUS_CHAPTER_SELECT";
const std::string NavigationEvents::EventNavigateHexusOpponentSelect = "EVENT_NAVIGATE_HEXUS_OPPONENT_SELECT";
const std::string NavigationEvents::EventNavigateCombat = "EVENT_NAVIGATE_COMBAT";
const std::string NavigationEvents::EventNavigateCutscene = "EVENT_NAVIGATE_CUTSCENE";

void NavigationEvents::navigateBack(int backCount)
{
	GlobalDirector::navigateBack(backCount);
}

void NavigationEvents::navigateTitle()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateTitle
	);
}

void NavigationEvents::navigateLoadingScreen(NavigateLoadingScreenArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateLoadingScreen,
		&args
	);
}

void NavigationEvents::navigateMap(NavigateMapArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateMap,
		&args
	);
}

void NavigationEvents::navigateSaveSelect()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateSaveSelect
	);
}

void NavigationEvents::navigateMinigames()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateMinigames
	);
}

void NavigationEvents::navigateOptions()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateOptions
	);
}

void NavigationEvents::navigateWorldMap()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateWorldMap
	);
}

void NavigationEvents::navigateHexus(NavigateHexusArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexus,
		&args
	);
}

void NavigationEvents::navigateHexusPuzzles()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusPuzzles
	);
}

void NavigationEvents::navigateHexusRewards(NavigateHexusRewardArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusRewards,
		&args
	);
}

void NavigationEvents::navigateHexusDeckManagement()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusDeckManagement
	);
}

void NavigationEvents::navigateHexusShop()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusShop
	);
}

void NavigationEvents::navigateHexusChapterSelect()
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusChapterSelect
	);
}

void NavigationEvents::navigateHexusOpponentSelect(NavigateHexusOpponentSelectArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateHexusOpponentSelect,
		&args
	);
}

void NavigationEvents::navigateCombat(NavigateCombatArgs args)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::EventNavigateCombat,
		&args
	);
}

void NavigationEvents::navigateCutscene(NavigateCutsceneArgs args)
{
	GlobalDirector::loadScene(args.cutscene);
}
