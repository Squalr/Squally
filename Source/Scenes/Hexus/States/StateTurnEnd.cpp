#include "StateTurnEnd.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/Sound.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/HexusConfig.h"

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
	this->increment0Sound = Sound::create(SoundResources::Hexus_Attacks_WindReverse);

	this->addChild(increment0Sound);
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

	float endTurnDelay = HexusConfig::endTurnDelay;
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
			DelayTime::create(HexusConfig::betweenTurnDelay),
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

		endTurnDelay = HexusConfig::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Enemy;
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(HexusConfig::betweenTurnDelay),
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
			DelayTime::create(HexusConfig::betweenTurnDelay),
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
			endTurnDelay = HexusConfig::enemyEndTurnDelay;
			gameState->turn = GameState::Turn::Player;
			CallFunc* changeState = CallFunc::create([gameState]
			{
				GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
			});

			this->runAction(Sequence::create(
				DelayTime::create(endTurnDelay),
				DelayTime::create(HexusConfig::betweenTurnDelay),
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
				DelayTime::create(HexusConfig::betweenTurnDelay),
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

	for (auto next : allFieldCards)
	{
		if (next->cardData->getCardKey() == CardKeys::Hex0)
		{
			next->addOperation(Card::Operation(Card::Operation::OperationType::ADD, 0b0001));
			next->cardEffects->runEffect(CardEffects::CardEffect::Nether);

			wasEffectRun = true;
		}
	}

	if (wasEffectRun)
	{
		this->increment0Sound->play();
	}
}
