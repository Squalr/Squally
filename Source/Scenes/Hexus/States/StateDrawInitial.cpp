#include "StateDrawInitial.h"

StateDrawInitial* StateDrawInitial::create()
{
	StateDrawInitial* instance = new StateDrawInitial();

	instance->autorelease();

	return instance;
}

StateDrawInitial::StateDrawInitial() : StateBase(GameState::StateType::DrawInitialCards)
{
}

StateDrawInitial::~StateDrawInitial()
{
}

void StateDrawInitial::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateDrawInitial::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	// Draw starting cards
	int drawnCount = 0;

	while (gameState->playerDeck->hasCards() && drawnCount < Config::startingCardAmount)
	{
		gameState->playerHand->insertCard(gameState->playerDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	drawnCount = 0;

	while (gameState->enemyDeck->hasCards() && drawnCount < Config::startingCardAmount)
	{
		gameState->enemyHand->insertCard(gameState->enemyDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::RoundStart);
		}),
		nullptr
	));
}

void StateDrawInitial::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateDrawInitial::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
