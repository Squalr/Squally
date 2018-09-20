#include "HexusEvents.h"

const std::string HexusEvents::HexusGameStartEvent = "hexus_game_start_event";

void HexusEvents::startGame(HexusGameEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::HexusGameStartEvent,
		&args
	);
}
