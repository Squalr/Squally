#include "NavigationEvents.h"

const std::string NavigationEvents::EventNavigateTitle = "EVENT_NAVIGATE_TITLE";
const std::string NavigationEvents::EventNavigateWorldMap = "EVENT_NAVIGATE_WORLD_MAP";

/*
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
	GlobalDirector::getInstance()->loadScene(cutscene);
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

void NavigationEvents::enterCombat(std::string levelFile, Squally* squally, PlatformerEnemy* enemy)
{
	NavigateFightArgs args = NavigateFightArgs(levelFile, squally, enemy);

	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		NavigationEvents::gameNavigateEnterCombatEvent,
		&args
	);
}
*/
