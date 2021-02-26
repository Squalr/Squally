#include "NormalFadeHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

using namespace cocos2d;

NormalFadeHud* NormalFadeHud::create()
{
	NormalFadeHud* instance = new NormalFadeHud();

	instance->autorelease();

	return instance;
}

NormalFadeHud::NormalFadeHud()
{
	this->fadeScreen = DrawNode::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->fadeScreen->drawSolidRect(Vec2::ZERO, Vec2(visibleSize), Color4F::BLACK);
	this->fadeScreen->setOpacity(0);
	
	this->addChild(this->fadeScreen);
}

NormalFadeHud::~NormalFadeHud()
{
}

void NormalFadeHud::runAnim()
{
	const float duration = 0.5f;

	this->fadeScreen->runAction(FadeTo::create(duration, 255));
}

void NormalFadeHud::resetAnim()
{
	const float duration = 0.5f;

	this->fadeScreen->setOpacity(0);
}
