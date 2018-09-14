#include "CoinFlip.h"

CoinFlip* CoinFlip::create()
{
	CoinFlip* instance = new CoinFlip();

	instance->autorelease();

	return instance;
}

CoinFlip::CoinFlip()
{
	this->coin = Sprite::create(Resources::Minigames_CoinFlipLion);
	this->skeletonInAnimation = Animation::create();
	this->skeletonOutAnimation = Animation::create();
	this->lionInAnimation = Animation::create();
	this->lionOutAnimation = Animation::create();
	this->neutralAnimation = Animation::create();

	this->skeletonInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipSkeletonIn1);
	this->skeletonInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipSkeletonIn2);
	this->skeletonInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipSkeleton);
	this->skeletonOutAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipSkeletonOut1);
	this->skeletonOutAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipSkeletonOut2);
	this->skeletonInAnimation->retain();
	this->skeletonOutAnimation->retain();

	this->lionInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipLionIn1);
	this->lionInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipLionIn2);
	this->lionInAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipLion);
	this->lionOutAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipLionOut1);
	this->lionOutAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipLionOut2);
	this->lionInAnimation->retain();
	this->lionOutAnimation->retain();

	this->neutralAnimation->addSpriteFrameWithFileName(Resources::Minigames_CoinFlipNeutral);
	this->neutralAnimation->retain();

	this->lionInAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->lionOutAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->skeletonInAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->skeletonOutAnimation->setDelayPerUnit(Config::coinFlipSpeed);
	this->neutralAnimation->setDelayPerUnit(Config::coinFlipSpeed);

	this->coin->setOpacity(0);

	this->addChild(this->coin);
}

CoinFlip::~CoinFlip()
{
}

void CoinFlip::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void CoinFlip::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->coin->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void CoinFlip::initializeListeners()
{
}

void CoinFlip::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::StateType::CoinFlip) {
		this->doCoinFlip(gameState);
	}
}

void CoinFlip::doCoinFlip(GameState* gameState)
{
	// TEMP: ALWAYS PLAYER 1st
	if (true || RandomHelper::random_real(0.0f, 1.0f) > 0.5f)
	{
		gameState->bannerMessage = "YOU GO FIRST";
		gameState->turn = GameState::Turn::Player;
	}
	else
	{
		gameState->bannerMessage = "ENEMY GOES FIRST";
		gameState->turn = GameState::Turn::Enemy;
	}

	this->coin->setScale(Config::coinFlipStartScale);
	this->coin->runAction(FadeTo::create(0.25f, 255));

	CallFunc* onCoinFlipEnd = CallFunc::create([gameState]
	{
		GameState::updateState(gameState, GameState::StateType::FirstSideBanner);
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
			DelayTime::create(Config::coinFlipBannerDisplayDelay),
			onCoinFlipEnd,
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
			DelayTime::create(Config::coinFlipBannerDisplayDelay),
			onCoinFlipEnd,
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
		nullptr));
}
