#include "PassIndicators.h"

PassIndicators* PassIndicators::create()
{
	PassIndicators* instance = new PassIndicators();

	instance->autorelease();

	return instance;
}

PassIndicators::PassIndicators()
{
	this->playerPassIndicator = Sprite::create(Resources::Minigames_Hexus_Flags);
	this->enemyPassIndicator = Sprite::create(Resources::Minigames_Hexus_Flags);

	this->playerPassIndicator->setOpacity(0);
	this->enemyPassIndicator->setOpacity(0);

	this->addChild(this->playerPassIndicator);
	this->addChild(this->enemyPassIndicator);
}

PassIndicators::~PassIndicators()
{
}

void PassIndicators::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassIndicator->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::playerPassIndicatorOffsetX, visibleSize.height / 2.0f + Config::playerPassIndicatorOffsetY);
	this->enemyPassIndicator->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::enemyPassIndicatorOffsetX, visibleSize.height / 2.0f + Config::enemyPassIndicatorOffsetY);
}

void PassIndicators::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::RoundEnd:
		case GameState::StateType::RoundStart:
			this->playerPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 0));
			this->enemyPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 0));
			break;
		default:
			break;
	}
}

void PassIndicators::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass)
	{
		switch (gameState->turn)
		{
			case GameState::Turn::Player:
				this->playerPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 255));
				break;
			case GameState::Turn::Enemy:
				this->enemyPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 255));
				break;
			default:
				break;
		}
	}
}
