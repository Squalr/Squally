#include "GameState.h"

const std::string GameState::onStateUpdateEvent = "on_state_update_event";

GameState::GameState(StateType stateType,
	Turn turn,
	Difficulty difficulty,
	int playerLosses,
	int enemyLosses,
	Card* stagedSacrifice,
	Card* selectedCard,
	std::string bannerMessage,
	std::function<void(Card*)> cardPreviewCallback,
	std::function<void(bool)> updateStateCallback,
	std::function<void()> endTurnCallback,
	std::function<void(GameState*)> requestAiCallback)
	: stateType(stateType),
	difficulty(difficulty),
	playerLosses(playerLosses),
	enemyLosses(enemyLosses),
	stagedSacrifice(stagedSacrifice),
	selectedCard(selectedCard),
	cardPreviewCallback(cardPreviewCallback),
	updateStateCallback(updateStateCallback),
	endTurnCallback(endTurnCallback),
	requestAiCallback(requestAiCallback)
{
}

GameState::~GameState()
{
}
