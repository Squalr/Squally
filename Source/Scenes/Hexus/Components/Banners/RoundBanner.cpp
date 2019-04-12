#include "RoundBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/FinalRound.h"
#include "Strings/Hexus/Banners/NextRound.h"
#include "Strings/Hexus/Banners/RoundStart.h"

using namespace cocos2d;

RoundBanner* RoundBanner::create()
{
	RoundBanner* instance = new RoundBanner();

	instance->autorelease();

	return instance;
}

RoundBanner::RoundBanner()
{
	this->roundBanner1 = Sprite::create(HexusResources::RoundBanner);
	this->roundBanner2 = Sprite::create(HexusResources::RoundBanner);

	this->addBannerChild(this->roundBanner1);
	this->addBannerChild(this->roundBanner2);
}

RoundBanner::~RoundBanner()
{
}

void RoundBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->roundBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->roundBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void RoundBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void RoundBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::RoundStart)
	{
		switch (gameState->roundNumber)
		{
			case 0:
			{
				this->setBannerText(Strings::Hexus_Banners_RoundStart::create());
				break;
			}
			case 1:
			{
				this->setBannerText(Strings::Hexus_Banners_NextRound::create());
				break;
			}
			case 2:
			default:
			{
				this->setBannerText(Strings::Hexus_Banners_FinalRound::create());
				break;
			}
		}

		this->flashBanner();
	}
}
