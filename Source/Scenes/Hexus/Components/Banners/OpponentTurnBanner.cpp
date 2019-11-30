#include "OpponentTurnBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

OpponentTurnBanner* OpponentTurnBanner::create()
{
	OpponentTurnBanner* instance = new OpponentTurnBanner();

	instance->autorelease();

	return instance;
}

OpponentTurnBanner::OpponentTurnBanner()
{
	this->enemyBanner1 = Sprite::create(HexusResources::EnemyBanner);
	this->enemyBanner2 = Sprite::create(HexusResources::EnemyBanner);

	this->setBannerText(Strings::Hexus_Banners_OpponentsTurn::create());

	this->addBannerChild(this->enemyBanner1);
	this->addBannerChild(this->enemyBanner2);
}

OpponentTurnBanner::~OpponentTurnBanner()
{
}

void OpponentTurnBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentTurnBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentTurnBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	// Only show after the first turn -- first turn is reserved for OpponentFirstBanner
	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::StateType::OpponentTurnStart && (gameState->roundNumber >=1 || gameState->turnNumber >= 1))
	{
		this->flashBanner();
	}
}
