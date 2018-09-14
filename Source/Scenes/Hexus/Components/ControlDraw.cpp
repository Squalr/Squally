#include "ControlDraw.h"

ControlDraw* ControlDraw::create()
{
	ControlDraw* instance = new ControlDraw();

	instance->autorelease();

	return instance;
}

ControlDraw::ControlDraw()
{
}

ControlDraw::~ControlDraw()
{
}

void ControlDraw::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlDraw::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlDraw::initializeListeners()
{
}

void ControlDraw::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::StateType::DrawInitialCards) {
		this->doInitialCardDraw(gameState);
	}

	if (gameState->stateType == GameState::StateType::Draw) {
		this->doCardDraw(gameState);
	}
}

void ControlDraw::doInitialCardDraw(GameState* gameState)
{
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

	GameState::updateState(gameState, GameState::StateType::ControlReplaceCards);
}

void ControlDraw::doCardDraw(GameState* gameState)
{
	CallFunc* stateTransition = CallFunc::create([gameState]
	{
		GameState::updateState(gameState, GameState::StateType::ControlNeutral);
	});

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
			stateTransition,
			nullptr
		));
		break;
	}
	case GameState::Turn::Player:
	default:
	{
		if (!gameState->playerDeck->hasCards())
		{
			this->runAction(Sequence::create(
				stateTransition,
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
			stateTransition,
			nullptr
		));

		break;
	}
	}
}
