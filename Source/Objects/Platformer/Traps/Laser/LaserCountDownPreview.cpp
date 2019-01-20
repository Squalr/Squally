#include "LaserCountDownPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Objects/Platformer/Traps/Laser/LaserAnimation.h"

using namespace cocos2d;

LaserCountDownPreview* LaserCountDownPreview::create()
{
	LaserCountDownPreview* instance = new LaserCountDownPreview();

	instance->autorelease();

	return instance;
}

LaserCountDownPreview::LaserCountDownPreview()
{
	this->previewLaser = LaserAnimation::create(480.0f);

	this->previewLaser->setScale(0.4f);

	this->previewNode->addChild(this->previewLaser);
}

HackablePreview* LaserCountDownPreview::clone()
{
	return LaserCountDownPreview::create();
}

void LaserCountDownPreview::onEnter()
{
	super::onEnter();

	this->runAction(RepeatForever::create(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->previewLaser->runAnimation();
		}),
		DelayTime::create(3.0f),
		nullptr
	)));
}

void LaserCountDownPreview::initializePositions()
{
	super::initializePositions();
}
