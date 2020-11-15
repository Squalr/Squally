#include "LossesDisplay.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

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
	super::onEnter();

	this->playerSkullA->setOpacity(0);
	this->playerSkullB->setOpacity(0);
	this->enemySkullA->setOpacity(0);
	this->enemySkullB->setOpacity(0);
}

void LossesDisplay::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerSocketA->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketAOffsetX, visibleSize.height / 2.0f - HexusConfig::socketOffsetY);
	this->playerSocketB->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketBOffsetX, visibleSize.height / 2.0f - HexusConfig::socketOffsetY);
	this->playerSkullA->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketAOffsetX, visibleSize.height / 2.0f - HexusConfig::socketOffsetY);
	this->playerSkullB->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketBOffsetX, visibleSize.height / 2.0f - HexusConfig::socketOffsetY);
	this->enemySocketA->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketAOffsetX, visibleSize.height / 2.0f + HexusConfig::socketOffsetY);
	this->enemySocketB->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketBOffsetX, visibleSize.height / 2.0f + HexusConfig::socketOffsetY);
	this->enemySkullA->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketAOffsetX, visibleSize.height / 2.0f + HexusConfig::socketOffsetY);
	this->enemySkullB->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::socketBOffsetX, visibleSize.height / 2.0f + HexusConfig::socketOffsetY);
}

void LossesDisplay::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void LossesDisplay::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	this->updateDisplayedLosses(gameState);
}

void LossesDisplay::updateDisplayedLosses(GameState* gameState)
{
	if (gameState->playerLosses >= 2)
	{
		this->playerSkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
		this->playerSkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
	}
	else if (gameState->playerLosses >= 1)
	{
		this->playerSkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
		this->playerSkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}
	else
	{
		this->playerSkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
		this->playerSkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}

	if (gameState->enemyLosses >= 2)
	{
		this->enemySkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
		this->enemySkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
	}
	else if (gameState->enemyLosses >= 1)
	{
		this->enemySkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
		this->enemySkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}
	else
	{
		this->enemySkullA->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
		this->enemySkullB->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}
}
