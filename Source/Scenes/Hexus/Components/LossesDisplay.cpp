#include "LossesDisplay.h"

LossesDisplay* LossesDisplay::create()
{
	LossesDisplay* instance = new LossesDisplay();

	instance->autorelease();

	return instance;
}

LossesDisplay::LossesDisplay()
{
	this->playerSocketA = Sprite::create(Resources::Minigames_Hexus_Socket);
	this->playerSocketB = Sprite::create(Resources::Minigames_Hexus_Socket);
	this->playerSkullA = Sprite::create(Resources::Minigames_Hexus_Skull);
	this->playerSkullA->setOpacity(0);
	this->playerSkullB = Sprite::create(Resources::Minigames_Hexus_Skull);
	this->playerSkullB->setOpacity(0);
	this->enemySocketA = Sprite::create(Resources::Minigames_Hexus_Socket);
	this->enemySocketB = Sprite::create(Resources::Minigames_Hexus_Socket);
	this->enemySkullA = Sprite::create(Resources::Minigames_Hexus_Skull);
	this->enemySkullA->setOpacity(0);
	this->enemySkullB = Sprite::create(Resources::Minigames_Hexus_Skull);
	this->enemySkullB->setOpacity(0);

	this->addChild(this->playerSocketA);
	this->addChild(this->playerSocketB);
	this->addChild(this->playerSkullA);
	this->addChild(this->playerSkullB);
	this->addChild(this->enemySocketA);
	this->addChild(this->enemySocketB);
	this->addChild(this->enemySkullA);
	this->addChild(this->enemySkullB);
}

LossesDisplay::~LossesDisplay()
{
}

void LossesDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerSocketA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSocketB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSkullA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSkullB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->enemySocketA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySocketB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySkullA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySkullB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
}

void LossesDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void LossesDisplay::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	this->updateDisplayedLosses(gameState);
}

void LossesDisplay::updateDisplayedLosses(GameState* gameState)
{
	if (gameState->playerLosses >= 2)
	{
		this->playerSkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
		this->playerSkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
	}
	else if (gameState->playerLosses >= 1)
	{
		this->playerSkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
		this->playerSkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}
	else
	{
		this->playerSkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
		this->playerSkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}

	if (gameState->enemyLosses >= 2)
	{
		this->enemySkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
		this->enemySkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
	}
	else if (gameState->enemyLosses >= 1)
	{
		this->enemySkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
		this->enemySkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}
	else
	{
		this->enemySkullA->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
		this->enemySkullB->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}
}