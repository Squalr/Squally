#include "OpponentPassBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/OpponentPassed.h"

using namespace cocos2d;

OpponentPassBanner* OpponentPassBanner::create()
{
	OpponentPassBanner* instance = new OpponentPassBanner();

	instance->autorelease();

	return instance;
}

OpponentPassBanner::OpponentPassBanner()
{
	this->opponentPassBanner1 = Sprite::create(HexusResources::EnemyPassBanner);
	this->opponentPassBanner2 = Sprite::create(HexusResources::EnemyPassBanner);

	this->setBannerText(Strings::Hexus_Banners_OpponentPassed::create());

	this->addBannerChild(this->opponentPassBanner1);
	this->addBannerChild(this->opponentPassBanner2);
}

OpponentPassBanner::~OpponentPassBanner()
{
}

void OpponentPassBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->opponentPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->opponentPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentPassBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentPassBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass && gameState->turn == GameState::Turn::Enemy && gameState->isEnemyPassCondition())
	{
		this->flashBanner();
	}
}
