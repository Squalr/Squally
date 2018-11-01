#include "StateDraw.h"

StateDraw* StateDraw::create()
{
	StateDraw* instance = new StateDraw();

	instance->autorelease();

	return instance;
}

StateDraw::StateDraw() : StateBase(GameState::StateType::Draw)
{
}

StateDraw::~StateDraw()
{
}

void StateDraw::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateDraw::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Enemy:
		{
			if (gameState->enemyDeck->hasCards())
			{
				// Simply insert the card directly into the enemy hand for the enemy
				gameState->enemyHand->insertCard(gameState->enemyDeck->drawCard(), 0.0f);
			}

			this->runAction(Sequence::create(
				DelayTime::create(Config::enemyDrawDelay),
				CallFunc::create([gameState]
				{
					GameState::updateState(gameState, GameState::StateType::AIDecideCard);
				}),
				nullptr
			));
			break;
		}
		case GameState::Turn::Player:
		{
			if (!gameState->playerDeck->hasCards())
			{
				this->runAction(Sequence::create(
					CallFunc::create([gameState]
					{
						GameState::updateState(gameState, GameState::StateType::Neutral);
					}),
					nullptr
				));

				return;
			}

			Card * card = gameState->playerDeck->drawCard();
			CardRow * hand = gameState->playerHand;

			GameUtils::changeParent(card, this, true);

			this->runAction(Sequence::create(
				CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, card, Config::cardDrawDelay)),
				DelayTime::create(Config::cardDrawDelay),
				DelayTime::create(Config::revealDelay),
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, card, Config::insertDelay)),
				DelayTime::create(Config::insertDelay),
				CallFunc::create([gameState]
				{
					GameState::updateState(gameState, GameState::StateType::Neutral);
				}),
				nullptr
			));

			break;
		}
		default:
			break;
	}
}

void StateDraw::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateDraw::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
