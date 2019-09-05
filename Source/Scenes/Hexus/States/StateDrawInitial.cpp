#include "StateDrawInitial.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

StateDrawInitial* StateDrawInitial::create()
{
	StateDrawInitial* instance = new StateDrawInitial();

	instance->autorelease();

	return instance;
}

StateDrawInitial::StateDrawInitial() : super(GameState::StateType::DrawInitialCards)
{
}

StateDrawInitial::~StateDrawInitial()
{
}

void StateDrawInitial::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateDrawInitial::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	const float indexDelay = 0.1f;

	// Draw starting cards
	std::vector<Card*> drawnCards = std::vector<Card*>();
	int playerDrawCount = gameState->roundNumber == 0 ? Config::startingCardAmount : gameState->playerCardsDrawnNextRound;

	for (int index = 0; index < playerDrawCount; index++)
	{
		if (!gameState->playerDeck->hasCards())
		{
			break;
		}

		Card* card = gameState->playerDeck->drawCard();

		GameUtils::changeParent(card, this, true);

		drawnCards.push_back(card);
	}

	this->runAction(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CardRow::insertCards, gameState->playerHand, drawnCards, Config::insertDelay, indexDelay, true)),
		nullptr
	));

	int enemyDrawCount = gameState->roundNumber == 0 ? Config::startingCardAmount : gameState->enemyCardsDrawnNextRound;

	for (int index = 0; index < enemyDrawCount; index++)
	{
		if (!gameState->enemyDeck->hasCards())
		{
			break;
		}

		gameState->enemyHand->insertCard(gameState->enemyDeck->drawCard(), 0.0f);
	}

	gameState->playerCardsDrawnNextRound = 0;
	gameState->enemyCardsDrawnNextRound = 0,

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::AIDecideCardReplace);
		}),
		nullptr
	));
}

void StateDrawInitial::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateDrawInitial::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
