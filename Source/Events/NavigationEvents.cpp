#pragma once
#include "NavigationEvents.h"

const std::string NavigationEvents::gameNavigateNewEvent = "game_navigate_new_event";
const std::string NavigationEvents::gameNavigateBackEvent = "game_navigate_back_event";
const std::string NavigationEvents::gameNavigateConfirmEvent = "game_navigate_confirm_event";
const std::string NavigationEvents::gameNavigateLoadLevelEvent = "game_navigate_load_level_event";
const std::string NavigationEvents::gameNavigateEnterLevelEvent = "game_navigate_enter_level_event";
const std::string NavigationEvents::gameNavigateLoadLevelEditorEvent = "game_navigate_load_level_editor_event";
const std::string NavigationEvents::gameNavigateEnterLevelEditorEvent = "game_navigate_enter_level_editor_event";
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

void NavigationEvents::loadLevel(std::string levelFile)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadLevelEvent,
		&NavigateLoadLevelArgs(levelFile)
	);
}

void NavigationEvents::enterLevel(LevelMap* levelMap)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateEnterLevelEvent,
		&NavigateEnterLevelArgs(levelMap)
	);
}

void NavigationEvents::loadLevelEditor(std::string levelFile, Vec2 initPosition)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadLevelEditorEvent,
		&NavigateLoadLevelEditorArgs(levelFile, initPosition)
	);
}

void NavigationEvents::enterLevelEditor(LevelMap* levelMap, Vec2 initPosition)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateEnterLevelEditorEvent,
		&NavigateEnterLevelEditorArgs(levelMap, initPosition)
	);
}

void NavigationEvents::loadFight(Player* player, Enemy* enemy)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateFightEvent,
		&NavigateFightArgs(player, enemy)
	);
}
