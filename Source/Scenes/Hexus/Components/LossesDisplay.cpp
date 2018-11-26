#include "LossesDisplay.h"

LossesDisplay* LossesDisplay::create()
{
	LossesDisplay* instance = new LossesDisplay();

	instance->autorelease();

	return instance;
}

LossesDisplay::LossesDisplay()
{
	this->playerSocketA = Sprite::create(HexusResources::Socket);
	this->playerSocketB = Sprite::create(HexusResources::Socket);
	this->playerSkullA = Sprite::create(HexusResources::Skull);
	this->playerSkullB = Sprite::create(HexusResources::Skull);
	this->enemySocketA = Sprite::create(HexusResources::Socket);
	this->enemySocketB = Sprite::create(HexusResources::Socket);
	this->enemySkullA = Sprite::create(HexusResources::Skull);
	this->enemySkullB = Sprite::create(HexusResources::Skull);

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

void LossesDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->playerSkullA->setOpacity(0);
	this->playerSkullB->setOpacity(0);
	this->enemySkullA->setOpacity(0);
	this->enemySkullB->setOpacity(0);
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

void LossesDisplay::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

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