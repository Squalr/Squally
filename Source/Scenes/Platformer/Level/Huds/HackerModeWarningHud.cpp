#include "HackerModeWarningHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

HackerModeWarningHud* HackerModeWarningHud::create()
{
	HackerModeWarningHud* instance = new HackerModeWarningHud();

	instance->autorelease();

	return instance;
}

HackerModeWarningHud::HackerModeWarningHud()
{
	this->radialEye = Sprite::create(UIResources::Combat_RadialEye);

	this->radialEye->setVisible(false);

	this->addChild(this->radialEye);
}

HackerModeWarningHud::~HackerModeWarningHud()
{
}

void HackerModeWarningHud::onEnter()
{
	super::onEnter();
}

void HackerModeWarningHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	static const Vec2 offset = Vec2(0.0f, -96.0f);
	
	this->radialEye->setPosition(visibleSize.width / 2.0f + offset.x - 128.0f, visibleSize.height + offset.y);
}

void HackerModeWarningHud::initializeListeners()
{
	super::initializeListeners();
}
