#include "ElectricityBeamCountDownPreview.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ElectricityBeamCountDownPreview* ElectricityBeamCountDownPreview::create()
{
	ElectricityBeamCountDownPreview* instance = new ElectricityBeamCountDownPreview();

	instance->autorelease();

	return instance;
}

ElectricityBeamCountDownPreview::ElectricityBeamCountDownPreview()
{
	this->launchCountDown = 0.0f;
	this->electricityAnimation = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);
	this->zbxTimerStr = ConstantString::create(std::to_string(this->launchCountDown));
	this->zbxTimer = this->createRegisterEqualsValueLabel(HackableCode::Register::zbx, false, this->zbxTimerStr);
	this->isLaunching = false;
	this->ballLeft = Sprite::create(ObjectResources::Traps_ElectricBeam_Ball);
	this->ballRight = Sprite::create(ObjectResources::Traps_ElectricBeam_Ball);

	this->zbxTimer->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->electricityAnimation->setScale(0.4f);
	this->ballLeft->setScale(0.4f);
	this->ballRight->setScale(0.4f);

	this->assemblyTextNode->addChild(this->zbxTimer);
	this->previewNode->addChild(this->electricityAnimation);
	this->previewNode->addChild(this->ballLeft);
	this->previewNode->addChild(this->ballRight);
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

	this->scheduleUpdate();
}

void ElectricityBeamCountDownPreview::initializePositions()
{
	super::initializePositions();
	
	this->zbxTimer->setPosition(Vec2(0.0f, 80.0f));
	this->ballLeft->setPosition(Vec2(-102.0f, 0.0f));
	this->ballRight->setPosition(Vec2(102.0f, 0.0f));
}

void ElectricityBeamCountDownPreview::update(float dt)
{
	super::update(dt);

	this->launchCountDown = MathUtils::clamp(this->launchCountDown - dt, 0.0f, 4.0f);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->launchCountDown;
	std::string s = stream.str();

	this->zbxTimerStr->setString(stream.str());
	
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
