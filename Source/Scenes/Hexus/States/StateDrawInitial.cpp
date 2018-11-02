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

	const float indexDelay = 0.1f;

	// Draw starting cards
	std::vector<Card*> drawnCards = std::vector<Card*>();
	int playerPenalty = gameState->enemyLastStanded ? gameState->penaltyCardsPlayed : 0;

	while (gameState->playerHand->getCardCount() + drawnCards.size() < Config::startingCardAmount - playerPenalty)
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
		CallFunc::create(CC_CALLBACK_0(CardRow::insertCards, gameState->playerHand, drawnCards, Config::insertDelay, indexDelay)),
		nullptr
	));

	int enemyPenalty = gameState->playerLastStanded ? gameState->penaltyCardsPlayed : 0;

	while (gameState->enemyHand->getCardCount() < Config::startingCardAmount - enemyPenalty)
	{
		if (!gameState->enemyDeck->hasCards())
		{
			break;
		}

		gameState->enemyHand->insertCard(gameState->enemyDeck->drawCard(), 0.0f);
	}

	// Reset last stand state
	gameState->penaltyCardsPlayed = 0;
	gameState->playerLastStanded = false;
	gameState->enemyLastStanded = false;

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
	StateBase::onStateReload(gameState);
}

void StateDrawInitial::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
