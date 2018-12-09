#include "ScoreTotal.h"

ScoreTotal* ScoreTotal::create()
{
	ScoreTotal* instance = new ScoreTotal();

	instance->autorelease();

	return instance;
}

ScoreTotal::ScoreTotal()
{
	this->playerTotalFrame = Sprite::create(HexusResources::ScoreBox);
	this->playerTotal = Label::createWithTTF("", Localization::getCodingFont(), 48.0f);
	this->playerTotal->enableOutline(Color4B::BLACK, 3);
	this->playerLeaderEmblem = Sprite::create(HexusResources::LeaderEmblem);

	this->enemyTotalFrame = Sprite::create(HexusResources::ScoreBox);
	this->enemyTotal = Label::createWithTTF("", Localization::getCodingFont(), 48.0f);
	this->enemyTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyLeaderEmblem = Sprite::create(HexusResources::LeaderEmblem);

	this->addChild(this->playerTotalFrame);
	this->addChild(this->playerLeaderEmblem);
	this->addChild(this->playerTotal);

	this->addChild(this->enemyTotalFrame);
	this->addChild(this->enemyLeaderEmblem);
	this->addChild(this->enemyTotal);
}

ScoreTotal::~ScoreTotal()
{
}

void ScoreTotal::onEnter()
{
	ComponentBase::onEnter();

	this->playerLeaderEmblem->setOpacity(0);
	this->enemyLeaderEmblem->setOpacity(0);
}

void ScoreTotal::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerTotalFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::totalAttackOffsetY);
	this->playerLeaderEmblem->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::leaderEmblemOffsetY);
	this->playerTotal->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::totalAttackOffsetY);

	this->enemyTotalFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::totalAttackOffsetY);
	this->enemyLeaderEmblem->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::leaderEmblemOffsetY);
	this->enemyTotal->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::totalAttackOffsetY);
}

void ScoreTotal::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void ScoreTotal::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	this->updateTotals(gameState);
}

void ScoreTotal::updateTotals(GameState* gameState)
{
	int playerTotalAttack = gameState->getPlayerTotal();
	int enemyTotalAttack = gameState->getEnemyTotal();

	this->playerTotal->setString(std::to_string(playerTotalAttack));
	this->enemyTotal->setString(std::to_string(enemyTotalAttack));

	this->playerLeaderEmblem->stopAllActions();
	this->enemyLeaderEmblem->stopAllActions();

	if (playerTotalAttack > enemyTotalAttack)
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
		this->enemyLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}
	else if (enemyTotalAttack > playerTotalAttack)
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
		this->enemyLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 255));
	}
	else
	{
		this->playerLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
		this->enemyLeaderEmblem->runAction(FadeTo::create(Config::skullFadeSpeed, 0));
	}
}
