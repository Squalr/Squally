#include "StateDraw.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

StateDraw* StateDraw::create()
{
	StateDraw* instance = new StateDraw();

	instance->autorelease();

	return instance;
}

StateDraw::StateDraw() : super(GameState::StateType::Draw)
{
}

StateDraw::~StateDraw()
{
}

void StateDraw::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateDraw::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

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

			Card* card = gameState->playerDeck->drawCard();
			CardRow* hand = gameState->playerHand;

			GameUtils::changeParent(card, this, true);

			this->runAction(Sequence::create(
				CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, card, Config::cardDrawDelay)),
				DelayTime::create(Config::cardDrawDelay),
				DelayTime::create(Config::revealDelay),
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, card, Config::insertDelay, true)),
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
		{
			break;
		}
	}
}

void StateDraw::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateDraw::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
