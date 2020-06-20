#include "ElectricityBeamGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ElectricityBeamGenericPreview* ElectricityBeamGenericPreview::create()
{
	ElectricityBeamGenericPreview* instance = new ElectricityBeamGenericPreview();

	instance->autorelease();

	return instance;
}

ElectricityBeamGenericPreview::ElectricityBeamGenericPreview()
{
	this->launchCountDown = 0.0f;
	this->electricityAnimation = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);
	this->isLaunching = false;
	this->ballLeft = Sprite::create(ObjectResources::Traps_ElectricBeam_Ball);
	this->ballRight = Sprite::create(ObjectResources::Traps_ElectricBeam_Ball);

	this->electricityAnimation->setScale(0.4f);
	this->ballLeft->setScale(0.4f);
	this->ballRight->setScale(0.4f);
	
	this->previewNode->addChild(this->electricityAnimation);
	this->previewNode->addChild(this->ballLeft);
	this->previewNode->addChild(this->ballRight);
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

	this->scheduleUpdate();
}

void ElectricityBeamGenericPreview::initializePositions()
{
	super::initializePositions();
	
	this->ballLeft->setPosition(Vec2(-102.0f, 0.0f));
	this->ballRight->setPosition(Vec2(102.0f, 0.0f));
}

void ElectricityBeamGenericPreview::update(float dt)
{
	super::update(dt);

	this->launchCountDown = MathUtils::clamp(this->launchCountDown - dt, 0.0f, 4.0f);
	
	if (!this->isLaunching && this->launchCountDown <= 0.0f)
	{
		this->isLaunching = true;

		this->electricityAnimation->playAnimation(ObjectResources::Traps_ElectricBeam_BeamFire_0000, 0.05f, true);

		this->runAction(Sequence::create(
			DelayTime::create(2.5f),
			CallFunc::create([=]()
			{
				this->launchCountDown = 1.0f;
				this->isLaunching = false;
			}),
			nullptr
		));
	}
}
