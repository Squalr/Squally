#include "ElectricityBeamCountDownPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Objects/Platformer/Traps/Laser/LaserAnimation.h"

using namespace cocos2d;

ElectricityBeamCountDownPreview* ElectricityBeamCountDownPreview::create()
{
	ElectricityBeamCountDownPreview* instance = new ElectricityBeamCountDownPreview();

	instance->autorelease();

	return instance;
}

ElectricityBeamCountDownPreview::ElectricityBeamCountDownPreview()
{
	this->previewLaser = LaserAnimation::create(480.0f);

	this->previewLaser->setScale(0.4f);

	this->previewNode->addChild(this->previewLaser);
}

ElectricityBeamCountDownPreview::~ElectricityBeamCountDownPreview()
{
}

HackablePreview* ElectricityBeamCountDownPreview::clone()
{
	return ElectricityBeamCountDownPreview::create();
}

void ElectricityBeamCountDownPreview::onEnter()
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

void ElectricityBeamCountDownPreview::initializePositions()
{
	super::initializePositions();
}
