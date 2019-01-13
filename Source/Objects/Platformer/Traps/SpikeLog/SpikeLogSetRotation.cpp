#include "SpikeLogSetRotation.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikeLogSetRotation* SpikeLogSetRotation::create()
{
	SpikeLogSetRotation* instance = new SpikeLogSetRotation();

	instance->autorelease();

	return instance;
}

SpikeLogSetRotation::SpikeLogSetRotation()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);

	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.5f, 0.0f);
	this->previewSpikedLog->setScale(0.25f);

	this->countString = ConstantString::create("0");

	if (sizeof(void*) == 4)
	{
		this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::ecx, true, this->countString);
	}
	else
	{
		this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::rcx, true, this->countString);
	}


	this->previewNode->addChild(this->previewSpikedLog);
	this->assemblyTextNode->addChild(this->ecxAnimationCount);
}

HackablePreview* SpikeLogSetRotation::clone()
{
	return SpikeLogSetRotation::create();
}

void SpikeLogSetRotation::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewSpikedLog->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius / 2.0f));

	/*
	this->previewSpikedLog->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug100->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 4.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug100->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);*/
}

void SpikeLogSetRotation::initializePositions()
{
	super::initializePositions();

	this->ecxAnimationCount->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius));
}
