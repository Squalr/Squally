#include "ElectricityBeamGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Objects/Platformer/Traps/Laser/LaserAnimation.h"

using namespace cocos2d;

ElectricityBeamGenericPreview* ElectricityBeamGenericPreview::create()
{
	ElectricityBeamGenericPreview* instance = new ElectricityBeamGenericPreview();

	instance->autorelease();

	return instance;
}

ElectricityBeamGenericPreview::ElectricityBeamGenericPreview()
{
	this->previewLaser = LaserAnimation::create(480.0f);

	this->previewLaser->setScale(0.4f);

	this->previewNode->addChild(this->previewLaser);
}

ElectricityBeamGenericPreview::~ElectricityBeamGenericPreview()
{
}

HackablePreview* ElectricityBeamGenericPreview::clone()
{
	return ElectricityBeamGenericPreview::create();
}

void ElectricityBeamGenericPreview::onEnter()
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

void ElectricityBeamGenericPreview::initializePositions()
{
	super::initializePositions();
}
