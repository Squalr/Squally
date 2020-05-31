#include "LaserGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Objects/Platformer/Traps/Laser/LaserAnimation.h"

using namespace cocos2d;

LaserGenericPreview* LaserGenericPreview::create()
{
	LaserGenericPreview* instance = new LaserGenericPreview();

	instance->autorelease();

	return instance;
}

LaserGenericPreview::LaserGenericPreview()
{
	this->previewLaser = LaserAnimation::create(480.0f);

	this->previewLaser->setScale(0.4f);

	this->previewNode->addChild(this->previewLaser);
}

LaserGenericPreview::~LaserGenericPreview()
{
}

HackablePreview* LaserGenericPreview::clone()
{
	return LaserGenericPreview::create();
}

void LaserGenericPreview::onEnter()
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

void LaserGenericPreview::initializePositions()
{
	super::initializePositions();
}
