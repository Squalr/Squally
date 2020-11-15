#include "ScoreTotal.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

ScoreTotal* ScoreTotal::create()
{
	ScoreTotal* instance = new ScoreTotal();

	instance->autorelease();

	return instance;
}

ScoreTotal::ScoreTotal()
{
	this->playerTotalFrame = Sprite::create(HexusResources::ScoreBox);
	this->playerTotalStr = ConstantString::create("0");
	this->playerTotalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->playerTotalStr);
	this->playerTotalLabel->enableOutline(Color4B::BLACK, 3);
	this->playerLeaderEmblem = Sprite::create(HexusResources::LeaderEmblem);

	this->enemyTotalFrame = Sprite::create(HexusResources::ScoreBox);
	this->enemyTotalStr = ConstantString::create("0");
	this->enemyTotalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->enemyTotalStr);
	this->enemyTotalLabel->enableOutline(Color4B::BLACK, 3);
	this->enemyLeaderEmblem = Sprite::create(HexusResources::LeaderEmblem);

	this->addChild(this->playerTotalFrame);
	this->addChild(this->playerLeaderEmblem);
	this->addChild(this->playerTotalLabel);

	this->addChild(this->enemyTotalFrame);
	this->addChild(this->enemyLeaderEmblem);
	this->addChild(this->enemyTotalLabel);
}

ScoreTotal::~ScoreTotal()
{
}

void ScoreTotal::onEnter()
{
	super::onEnter();

	this->playerLeaderEmblem->setOpacity(0);
	this->enemyLeaderEmblem->setOpacity(0);
}

void ScoreTotal::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerTotalFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f - HexusConfig::totalAttackOffsetY);
	this->playerLeaderEmblem->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f - HexusConfig::leaderEmblemOffsetY);
	this->playerTotalLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f - HexusConfig::totalAttackOffsetY);

	this->enemyTotalFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f + HexusConfig::totalAttackOffsetY);
	this->enemyLeaderEmblem->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f + HexusConfig::leaderEmblemOffsetY);
	this->enemyTotalLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::totalAttackOffsetX, visibleSize.height / 2.0f + HexusConfig::totalAttackOffsetY);
}

void ScoreTotal::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void ScoreTotal::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	this->updateTotals(gameState);
}

void ScoreTotal::updateTotals(GameState* gameState)
{
	int playerTotalAttack = gameState->getPlayerTotal();
	int enemyTotalAttack = gameState->getEnemyTotal();

	this->playerTotalStr->setString(std::to_string(playerTotalAttack));
	this->enemyTotalStr->setString(std::to_string(enemyTotalAttack));

	this->playerLeaderEmblem->stopAllActions();
	this->enemyLeaderEmblem->stopAllActions();

	if (playerTotalAttack > enemyTotalAttack)
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
		this->enemyLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}
	else if (enemyTotalAttack > playerTotalAttack)
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
		this->enemyLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 255));
	}
	else
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
		this->enemyLeaderEmblem->runAction(FadeTo::create(HexusConfig::skullFadeSpeed, 0));
	}
}
