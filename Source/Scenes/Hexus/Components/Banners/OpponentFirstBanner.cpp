#include "OpponentFirstBanner.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

OpponentFirstBanner* OpponentFirstBanner::create()
{
	OpponentFirstBanner* instance = new OpponentFirstBanner();

	instance->autorelease();

	return instance;
}

OpponentFirstBanner::OpponentFirstBanner()
{
	this->enemyBanner1 = Sprite::create(HexusResources::EnemyBanner);
	this->enemyBanner2 = Sprite::create(HexusResources::EnemyBanner);

	this->setBannerText(Strings::Hexus_Banners_OpponentFirst::create());

	this->addBannerChild(this->enemyBanner1);
	this->addBannerChild(this->enemyBanner2);
}

OpponentFirstBanner::~OpponentFirstBanner()
{
}

void OpponentFirstBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentFirstBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentFirstBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	// First mover banner does not apply to games with initial states
	if (gameState->opponentData->stateOverride != nullptr)
	{
		return;
	}

	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::StateType::OpponentTurnStart && gameState->roundNumber == 0 && gameState->turnNumber == 0)
	{
		this->flashBanner();
	}
}
