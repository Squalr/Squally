#include "StateCoinFlip.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

StateCoinFlip* StateCoinFlip::create()
{
	StateCoinFlip* instance = new StateCoinFlip();

	instance->autorelease();

	return instance;
}

StateCoinFlip::StateCoinFlip() : super(GameState::StateType::CoinFlip)
{
	this->coinAnimation = SmartAnimationSequenceNode::create(HexusResources::CoinFlip_0000);

	this->addChild(this->coinAnimation);
}

StateCoinFlip::~StateCoinFlip()
{
}

void StateCoinFlip::onEnter()
{
	super::onEnter();

	this->coinAnimation->setOpacity(0);
}

void StateCoinFlip::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->coinAnimation->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void StateCoinFlip::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateCoinFlip::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

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

	this->coinAnimation->setScale(Config::coinFlipStartScale);
	this->coinAnimation->runAction(FadeTo::create(0.25f, 255));

	this->coinAnimation->runAction(Sequence::create(
		DelayTime::create(Config::coinFlipStartDelay),
		CallFunc::create([=]()
		{
			switch (gameState->turn)
			{
				case GameState::Turn::Player:
				{
					this->coinAnimation->playAnimationRepeat(HexusResources::CoinFlip_0000, Config::coinFlipSpeed, 0.0f, false, Config::coinFlipCount, [=]()
					{
						this->coinAnimation->playAnimation(std::vector<std::string>({ HexusResources::CoinFlip_0000 }), Config::coinFlipSpeed);
					});

					break;
				}
				case GameState::Turn::Enemy:
				{
					this->coinAnimation->playAnimationRepeat(HexusResources::CoinFlip_0000, Config::coinFlipSpeed, 0.0f, false, Config::coinFlipCount, [=]()
					{
						this->coinAnimation->playAnimation({ HexusResources::CoinFlip_0000, HexusResources::CoinFlip_0001, HexusResources::CoinFlip_0002, HexusResources::CoinFlip_0003, HexusResources::CoinFlip_0004, HexusResources::CoinFlip_0005, HexusResources::CoinFlip_0006 }, Config::coinFlipSpeed);
					});
					break;
				}
			}
		}),
		EaseSineOut::create(ScaleTo::create(Config::coinFlipUpDuration, Config::coinFlipEndScale)),
		EaseSineOut::create(ScaleTo::create(Config::coinFlipDownDuration, Config::coinFlipStartScale)),
		CallFunc::create([=]()
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
		}),
		DelayTime::create(Config::coinFlipRestDuration),
		FadeOut::create(Config::coinFlipFadeSpeed),
		nullptr
	));
}

void StateCoinFlip::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateCoinFlip::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
