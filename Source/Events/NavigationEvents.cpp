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
	NavigateBackEventArgs args = NavigateBackEventArgs(count);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateBackEvent,
		&args
	);
}

void NavigationEvents::navigate(GameScreen gameScreen)
{
	NavigateEventArgs args = NavigateEventArgs(gameScreen);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateNewEvent,
		&args
	);
}

void NavigationEvents::navigateConfirm(std::string confirmMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	NavigateConfirmArgs args = NavigateConfirmArgs(confirmMessage, confirmCallback, cancelCallback);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateConfirmEvent,
		&args
	);
}

void NavigationEvents::loadCutscene(Cutscene* cutscene)
{
	NavigateLoadCutsceneArgs args = NavigateLoadCutsceneArgs(cutscene);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadCutsceneEvent,
		&args
	);
}

void NavigationEvents::loadMap(std::string levelFile)
{
	NavigateLoadLevelArgs args = NavigateLoadLevelArgs(levelFile);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateLoadLevelEvent,
		&args
	);
}

void NavigationEvents::enterLevel(SerializableMap* levelMap)
{
	NavigateEnterLevelArgs args = NavigateEnterLevelArgs(levelMap);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateEnterLevelEvent,
		&args
	);
}

void NavigationEvents::loadFight(Squally* squally, PlatformerEnemy* enemy)
{
	NavigateFightArgs args = NavigateFightArgs(squally, enemy);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateFightEvent,
		&args
	);
}
