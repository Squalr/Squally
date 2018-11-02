#include "StatePenaltyDiscard.h"

StatePenaltyDiscard* StatePenaltyDiscard::create()
{
	StatePenaltyDiscard* instance = new StatePenaltyDiscard();

	instance->autorelease();

	return instance;
}

StatePenaltyDiscard::StatePenaltyDiscard() : StateBase(GameState::StateType::PenaltyDiscard)
{
	this->penaltyIcon = Sprite::create(Resources::Minigames_Hexus_PenaltyCardsIconLarge);
	this->penaltyIconParticles = ParticleSystemQuad::create(Resources::Particles_PurpleAuraLarge);

	this->penaltyIcon->setOpacity(0);
	this->penaltyIconParticles->setVisible(false);

	this->addChild(this->penaltyIconParticles);
	this->addChild(this->penaltyIcon);
}

StatePenaltyDiscard::~StatePenaltyDiscard()
{
}

void StatePenaltyDiscard::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->penaltyIconParticles->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 256.0f));
	this->penaltyIcon->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 256.0f));
}

void StatePenaltyDiscard::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePenaltyDiscard::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	if (gameState->enemyLastStanded && gameState->penaltyCardsPlayed > 0 && gameState->playerHand->getCardCount() > 0)
	{
		this->penaltyIconParticles->start();
		this->penaltyIconParticles->setVisible(true);
		this->penaltyIcon->runAction(FadeTo::create(0.25f, 255));

		gameState->playerHand->enableRowCardInteraction();

		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameUtils::changeParent(gameState->playerHand, this, true);
		gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f)));
		gameState->playerHand->setCardScale(0.6f, 0.25f);
		gameState->playerHand->setRowWidth(Config::previewWidth, 0.25f);
		gameState->playerHand->enableRowCardInteraction();

		gameState = gameState;
		this->initializeCallbacks(gameState);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::AIDecideCardReplace);
			}),
			nullptr
		));
	}
}

void StatePenaltyDiscard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);

	if (gameState->penaltyCardsPlayed > 0 && gameState->playerHand->getCardCount() > 0)
	{
		gameState->playerHand->enableRowCardInteraction();

		gameState = gameState;
		this->initializeCallbacks(gameState);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::AIDecideCardReplace);
			}),
			nullptr
		));
	}
}

void StatePenaltyDiscard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	this->penaltyIconParticles->stop();
	this->penaltyIconParticles->setVisible(false);
	this->penaltyIcon->runAction(FadeTo::create(0.25f, 0));

	// Restore hand to proper position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->playerHand, gameState, true);
	gameState->playerHand->setCardScale(Card::cardScale, 0.25f);
	gameState->playerHand->setRowWidth(Config::handWidth, 0.25f);
	gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY)));

	// Clear last stand state
	gameState->penaltyCardsPlayed = 0;
	gameState->playerLastStanded = false;
	gameState->enemyLastStanded = false;
}

void StatePenaltyDiscard::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StatePenaltyDiscard::discardCard, this, gameState));
}

void StatePenaltyDiscard::discardCard(Card* cardToDiscard, GameState* gameState)
{
	if (gameState->penaltyCardsPlayed > 0)
	{
		cardToDiscard->disableInteraction();
		gameState->penaltyCardsPlayed--;
		gameState->playerHand->removeCard(cardToDiscard);
		gameState->playerGraveyard->insertCardBottom(cardToDiscard, false, 0.5f);

		// Either exit this state, or re-enter if not finished
		if (gameState->penaltyCardsPlayed <= 0)
		{
			gameState->playerHand->disableRowCardInteraction();

			this->runAction(Sequence::create(
				DelayTime::create(0.75f),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::AIDecideCardReplace);
				}),
				nullptr
			));
		}
		else
		{
			this->runAction(Sequence::create(
				DelayTime::create(0.75f),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::PenaltyDiscard);
				}),
				nullptr
			));
		}
	}
}
