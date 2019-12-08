#include "CombatFadeInHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

using namespace cocos2d;

const float CombatFadeInHud::AnimationTimeBudget = 0.75f;

CombatFadeInHud::CombatFadeInHud()
{
	this->blackout = DrawNode::create();

	this->buildBlackout();

	this->addChild(this->blackout);
}

CombatFadeInHud::~CombatFadeInHud()
{
}

void CombatFadeInHud::onEnter()
{
	super::onEnter();

	this->blackout->setOpacity(0);

	this->runAnim();
}

void CombatFadeInHud::fillSeams()
{
	this->blackout->setOpacity(255);
}

void CombatFadeInHud::buildBlackout()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->blackout->drawSolidRect(Vec2::ZERO, Vec2(visibleSize), Color4F::BLACK);
}
