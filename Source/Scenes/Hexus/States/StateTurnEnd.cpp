#include "StateTurnEnd.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/SoundManager.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

StateTurnEnd* StateTurnEnd::create()
{
	StateTurnEnd* instance = new StateTurnEnd();

	instance->autorelease();

	return instance;
}

StateTurnEnd::StateTurnEnd() : super(GameState::StateType::TurnEnd)
{
}

StateTurnEnd::~StateTurnEnd()
{
}

void StateTurnEnd::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);

	gameState->turnNumber++;
}

void StateTurnEnd::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->clearInteraction();

	if (!(gameState->enemyPassed && gameState->playerPassed))
	{
		this->runIncrementHex0Effect(gameState);
	}

	float endTurnDelay = Config::endTurnDelay;
	gameState->isRepeatingSameTurn = false;
	gameState->selectedRow = nullptr;
	gameState->selectedSourceCard = nullptr;
	gameState->selectedDestinationCard = nullptr;

	// If both players passed than we end the round
	if (gameState->playerPassed && gameState->enemyPassed)
	{
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::RoundEnd);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If the player passed it is the enemies turn
	if (gameState->playerPassed)
	{
		if (gameState->turn == GameState::Turn::Enemy)
		{
			gameState->isRepeatingSameTurn = true;
		}

		endTurnDelay = Config::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Enemy;
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If the enemy passed it is the players turn
	if (gameState->enemyPassed)
	{
		if (gameState->turn == GameState::Turn::Player)
		{
			gameState->isRepeatingSameTurn = true;
		}

		gameState->turn = GameState::Turn::Player;
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If no one has activated last stand we alternate turns
	switch (gameState->turn)
	{
		case GameState::Turn::Enemy:
		{
			endTurnDelay = Config::enemyEndTurnDelay;
			gameState->turn = GameState::Turn::Player;
			CallFunc* changeState = CallFunc::create([gameState]
			{
				GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
			});

			this->runAction(Sequence::create(
				DelayTime::create(endTurnDelay),
				DelayTime::create(Config::betweenTurnDelay),
				changeState,
				nullptr
			));
			break;
		}
		case GameState::Turn::Player:
		{
			gameState->turn = GameState::Turn::Enemy;

			CallFunc* changeState = CallFunc::create([gameState]
			{
				GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
			});

			this->runAction(Sequence::create(
				DelayTime::create(endTurnDelay),
				DelayTime::create(Config::betweenTurnDelay),
				changeState,
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

void StateTurnEnd::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateTurnEnd::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}

void StateTurnEnd::runIncrementHex0Effect(GameState* gameState)
{
	std::vector<Card*> allFieldCards = gameState->getAllCards();

	bool wasEffectRun = false;

	for (auto it = allFieldCards.begin(); it != allFieldCards.end(); it++)
	{
		if ((*it)->cardData->cardKey == CardKeys::Hex0)
		{
			(*it)->addOperation(Card::Operation(Card::Operation::OperationType::ADD, 0b0001));
			(*it)->cardEffects->runEffect(CardEffects::CardEffect::Nether);

			wasEffectRun = true;
		}
	}

	if (wasEffectRun)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Attacks_WindReverse);
	}
}
