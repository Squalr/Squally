#include "ScoreTotal.h"

ScoreTotal* ScoreTotal::create()
{
	ScoreTotal* instance = new ScoreTotal();

	instance->autorelease();

	return instance;
}

ScoreTotal::ScoreTotal()
{
	this->playerTotalFrame = Sprite::create(Resources::Minigames_Hexus_ScoreBox);
	this->playerTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerTotal->enableOutline(Color4B::BLACK, 3);
	this->playerLeaderEmblem = Sprite::create(Resources::Minigames_Hexus_LeaderEmblem);
	this->playerLeaderEmblem->setOpacity(0);

	this->enemyTotalFrame = Sprite::create(Resources::Minigames_Hexus_ScoreBox);
	this->enemyTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->enemyTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyLeaderEmblem = Sprite::create(Resources::Minigames_Hexus_LeaderEmblem);
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

void ScoreTotal::onStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
	switch(gameState->stateType) {
		case GameState::Score: 
		{
			gameState->endRound();
			if (gameState->playerLosses >= 2) 
			{
				GameState::updateState(gameState, GameState::StateType::Lose);
			}
			else if (gameState->enemyLosses >= 2) 
			{
				GameState::updateState(gameState, GameState::StateType::Win);
			}
			else 
			{
				// Player cannot enter the last round with zero cards
				if (gameState->playerHand->getCardCount() == 0) {
					GameState::updateState(gameState, GameState::StateType::Lose);
				} else {
					GameState::updateState(gameState, GameState::StateType::ControlReplaceCards);
				}
			}
		}
		default:
			break;
	}
	
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
