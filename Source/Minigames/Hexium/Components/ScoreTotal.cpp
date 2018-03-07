#include "ScoreTotal.h"

ScoreTotal* ScoreTotal::create()
{
	ScoreTotal* scoreTotal = new ScoreTotal();

	scoreTotal->autorelease();

	return scoreTotal;
}

ScoreTotal::ScoreTotal()
{
	this->playerTotalFrame = Sprite::create(Resources::Minigames_Hexium_ScoreBox);
	this->playerTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->playerTotal->enableOutline(Color4B::BLACK, 3);
	this->playerLeaderEmblem = Sprite::create(Resources::Minigames_Hexium_LeaderEmblem);
	this->playerLeaderEmblem->setOpacity(0);

	this->enemyTotalFrame = Sprite::create(Resources::Minigames_Hexium_ScoreBox);
	this->enemyTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->enemyTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyLeaderEmblem = Sprite::create(Resources::Minigames_Hexium_LeaderEmblem);
	this->enemyLeaderEmblem->setOpacity(0);

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

	this->initializePositions();
	this->initializeListeners();
}

void ScoreTotal::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerTotalFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::totalAttackOffsetY);
	this->playerLeaderEmblem->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::leaderEmblemOffsetY);
	this->playerTotal->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f - Config::totalAttackOffsetY);

	this->enemyTotalFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::totalAttackOffsetY);
	this->enemyLeaderEmblem->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::leaderEmblemOffsetY);
	this->enemyTotal->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX, visibleSize.height / 2.0f + Config::totalAttackOffsetY);
}

void ScoreTotal::initializeListeners()
{
}

void ScoreTotal::onStateChange(GameState* gameState)
{
	switch (gameState->stateType) {
	case GameState::StateType::ControlNeutral:
		break;
	}
}

void ScoreTotal::updateTotals(GameState* gameState)
{
	// TODO: Calculate these
	int playerTotalAttack = 66;
	int enemyTotalAttack = 123;

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
