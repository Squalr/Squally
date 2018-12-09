#include "StateCoinFlip.h"

#include "Resources/HexusResources.h"

StateCoinFlip* StateCoinFlip::create()
{
	StateCoinFlip* instance = new StateCoinFlip();

	instance->autorelease();

	return instance;
}

StateCoinFlip::StateCoinFlip() : StateBase(GameState::StateType::CoinFlip)
{
	this->coin = Sprite::create(HexusResources::CoinFlipLion);
	this->skeletonInAnimation = Animation::create();
	this->skeletonOutAnimation = Animation::create();
	this->lionInAnimation = Animation::create();
	this->lionOutAnimation = Animation::create();
	this->neutralAnimation = Animation::create();

	this->skeletonInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipSkeletonIn1);
	this->skeletonInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipSkeletonIn2);
	this->skeletonInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipSkeleton);
	this->skeletonOutAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipSkeletonOut1);
	this->skeletonOutAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipSkeletonOut2);
	this->skeletonInAnimation->retain();
	this->skeletonOutAnimation->retain();

	this->lionInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipLionIn1);
	this->lionInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipLionIn2);
	this->lionInAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipLion);
	this->lionOutAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipLionOut1);
	this->lionOutAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipLionOut2);
	this->lionInAnimation->retain();
	this->lionOutAnimation->retain();

	this->neutralAnimation->addSpriteFrameWithFileName(HexusResources::CoinFlipNeutral);
	this->neutralAnimation->retain();

	this->lionInAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->lionOutAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->skeletonInAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->skeletonOutAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->neutralAnimation->setDelayPerUnit(Config::coinFlipSpeed);

	this->addChild(this->coin);
}

StateCoinFlip::~StateCoinFlip()
{
}

void StateCoinFlip::onEnter()
{
	StateBase::onEnter();

	this->coin->setOpacity(0);
}

void StateCoinFlip::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->coin->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void StateCoinFlip::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateCoinFlip::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	// No coin flip after the first round
	if (gameState->roundNumber >= 1)
	{
		// Alternate turn instead
		gameState->turn = (gameState->turn == GameState::Turn::Player) ? GameState::Turn::Enemy : GameState::Turn::Player;
		
		switch (gameState->turn)
		{
			case GameState::Turn::Enemy:
			{
				this->runAction(Sequence::create(
					DelayTime::create(0.25f),
					CallFunc::create([=]()
					{
						GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
					}),
					nullptr
				));
				break;
			}
			default:
			case GameState::Turn::Player:
			{
				this->runAction(Sequence::create(
					DelayTime::create(0.25f),
					CallFunc::create([=]()
					{
						GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
					}),
					nullptr
				));
				break;
			}
		}

		return;
	}

	if (RandomHelper::random_real(0.0f, 1.0f) > 0.5f)
	{
		gameState->turn = GameState::Turn::Player;
	}
	else
	{
		gameState->turn = GameState::Turn::Enemy;
	}

	this->coin->setScale(Config::coinFlipStartScale);
	this->coin->runAction(FadeTo::create(0.25f, 255));

	CallFunc* onStateCoinFlipEnd = CallFunc::create([=]
	{
		switch (gameState->turn)
		{
			case GameState::Turn::Enemy:
			{
				GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
				break;
			}
			default:
			case GameState::Turn::Player:
			{
				GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
				break;
			}
		}
	});

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			Sequence* loopSequence = Sequence::create(
				Animate::create(this->lionInAnimation->clone()),
				Animate::create(this->lionOutAnimation->clone()),
				Animate::create(this->neutralAnimation->clone()),
				Animate::create(this->skeletonInAnimation->clone()),
				Animate::create(this->skeletonOutAnimation->clone()),
				Animate::create(this->neutralAnimation->clone()),
				nullptr);

			this->coin->runAction(Sequence::create(
				DelayTime::create(Config::coinFlipStartDelay),
				Repeat::create(loopSequence, Config::coinFlipCount),
				Animate::create(this->lionInAnimation->clone()),
				onStateCoinFlipEnd,
				nullptr));
			break;
		}
		case GameState::Turn::Enemy:
		{
			Sequence* loopSequence = Sequence::create(
				Animate::create(this->skeletonInAnimation->clone()),
				Animate::create(this->skeletonOutAnimation->clone()),
				Animate::create(this->neutralAnimation->clone()),
				Animate::create(this->lionInAnimation->clone()),
				Animate::create(this->lionOutAnimation->clone()),
				Animate::create(this->neutralAnimation->clone()),
				nullptr);

			this->coin->runAction(Sequence::create(
				DelayTime::create(Config::coinFlipStartDelay),
				Repeat::create(loopSequence, Config::coinFlipCount),
				Animate::create(this->skeletonInAnimation->clone()),
				onStateCoinFlipEnd,
				nullptr));
			break;
		}
	}

	this->coin->runAction(Sequence::create(
		DelayTime::create(Config::coinFlipStartDelay),
		EaseSineOut::create(ScaleTo::create(Config::coinFlipUpDuration, Config::coinFlipEndScale)),
		EaseSineOut::create(ScaleTo::create(Config::coinFlipDownDuration, Config::coinFlipStartScale)),
		DelayTime::create(Config::coinFlipRestDuration),
		FadeOut::create(Config::coinFlipFadeSpeed),
		nullptr
	));
}

void StateCoinFlip::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateCoinFlip::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
