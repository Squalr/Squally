#include "SpikeLogSetRotation.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

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
	this->previewHeavenHug100 = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);
	this->previewHeavenHug200 = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);
	this->previewHeavenHug400 = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);

	if (sizeof(void*) == 4)
	{
		this->eax100Height = this->createRegisterEqualsValueLabel(HackableCode::Register::eax, true, ConstantString::create("100f"));
		this->eax200Height = this->createRegisterEqualsValueLabel(HackableCode::Register::eax, true, ConstantString::create("200f"));
		this->eax400Height = this->createRegisterEqualsValueLabel(HackableCode::Register::eax, true, ConstantString::create("400f"));
	}
	else
	{
		this->eax100Height = this->createRegisterEqualsValueLabel(HackableCode::Register::rax, true, ConstantString::create("100f"));
		this->eax200Height = this->createRegisterEqualsValueLabel(HackableCode::Register::rax, true, ConstantString::create("200f"));
		this->eax400Height = this->createRegisterEqualsValueLabel(HackableCode::Register::rax, true, ConstantString::create("400f"));
	}

	this->previewNode->addChild(this->previewHeavenHug100);
	this->previewNode->addChild(this->previewHeavenHug200);
	this->previewNode->addChild(this->previewHeavenHug400);
	this->assemblyTextNode->addChild(this->eax100Height);
	this->assemblyTextNode->addChild(this->eax200Height);
	this->assemblyTextNode->addChild(this->eax400Height);
}

HackablePreview* SpikeLogSetRotation::clone()
{
	return SpikeLogSetRotation::create();
}

void SpikeLogSetRotation::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;
	const float topOffset = 48.0f;

	this->previewHeavenHug100->setPosition(Vec2(-96.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewHeavenHug400->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewHeavenHug200->setPosition(Vec2(96.0f, HackablePreview::PreviewRadius - offset - topOffset));

	this->previewHeavenHug100->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug100->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 4.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug100->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewHeavenHug200->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug200->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug200->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewHeavenHug400->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug400->getPositionX(), -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewHeavenHug400->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);
}

void SpikeLogSetRotation::initializePositions()
{
	super::initializePositions();

	this->eax100Height->setPosition(Vec2(-112.0f, HackablePreview::PreviewRadius - 48.0f));
	this->eax400Height->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius));
	this->eax200Height->setPosition(Vec2(112.0f, HackablePreview::PreviewRadius - 48.0f));
}
