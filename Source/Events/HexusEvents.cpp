#include "HexusEvents.h"

const std::string HexusEvents::HexusGameStartEvent = "hexus_game_start_event";
const std::string HexusEvents::HexusShowRewardsEvent = "hexus_show_rewards_event";

void HexusEvents::startGame(HexusGameEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::HexusGameStartEvent,
		&args
	);
}

void HexusEvents::showRewards(HexusRewardArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::HexusShowRewardsEvent,
		&args
	);
}
