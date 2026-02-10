#include "FadeHudBase.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCDrawNode.h"
#include "2d/CCSprite.h"
#include "base/CCDirector.h"

using namespace cocos2d;

FadeHudBase::FadeHudBase()
{
	this->blackout = DrawNode::create();

	this->buildBlackout();

	this->addChild(this->blackout);
}

FadeHudBase::~FadeHudBase()
{
}

void FadeHudBase::onEnter()
{
	super::onEnter();

	this->blackout->setOpacity(0);
}

void FadeHudBase::fillSeams()
{
	this->blackout->setOpacity(255);
}

void FadeHudBase::pause()
{
	// ignore
}

void FadeHudBase::buildBlackout()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->blackout->drawSolidRect(Vec2::ZERO, Vec2(visibleSize), Color4F::BLACK);
}
