#pragma once
#include "NavigationEvents.h"

const std::string NavigationEvents::gameNavigateNewEvent = "game_navigate_new_event";
const std::string NavigationEvents::gameNavigateBackEvent = "game_navigate_back_event";
const std::string NavigationEvents::gameNavigateConfirmEvent = "game_navigate_confirm_event";
const std::string NavigationEvents::gameNavigateLoadCutsceneEvent = "game_navigate_load_cutscene_event";
const std::string NavigationEvents::gameNavigateLoadLevelEvent = "game_navigate_load_level_event";
const std::string NavigationEvents::gameNavigateEnterLevelEvent = "game_navigate_enter_level_event";
const std::string NavigationEvents::gameNavigateFightEvent = "game_navigate_fight_event";

void NavigationEvents::navigateBack(int count)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateBackEvent,
		&NavigateBackEventArgs(count)
	);
}

void NavigationEvents::navigate(GameScreen gameScreen)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateNewEvent,
		&NavigateEventArgs(gameScreen)
	);
}

void NavigationEvents::navigateConfirm(std::string confirmMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateConfirmEvent,
		&NavigateConfirmArgs(confirmMessage, confirmCallback, cancelCallback)
	);
}

void NavigationEvents::loadCutscene(CutsceneSequence* cutscene)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadCutsceneEvent,
		&NavigateLoadCutsceneArgs(cutscene)
	);
}

void NavigationEvents::loadMap(std::string levelFile)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadLevelEvent,
		&NavigateLoadLevelArgs(levelFile)
	);
}

void NavigationEvents::enterLevel(SerializableMap* levelMap)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateEnterLevelEvent,
		&NavigateEnterLevelArgs(levelMap)
	);
}

void NavigationEvents::loadFight(Squally* squally, PlatformerEnemy* enemy)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateFightEvent,
		&NavigateFightArgs(squally, enemy)
	);
}
