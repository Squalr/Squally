#include "StalactiteSetSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

StalactiteSetSpeedPreview* StalactiteSetSpeedPreview::create()
{
	StalactiteSetSpeedPreview* instance = new StalactiteSetSpeedPreview();

	instance->autorelease();

	return instance;
}

StalactiteSetSpeedPreview::StalactiteSetSpeedPreview()
{
	this->previewStalactite100 = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);
	this->previewStalactite200 = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);
	this->previewStalactite400 = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);

	this->eax100Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("100f"));
	this->eax200Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("200f"));
	this->eax400Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("400f"));

	this->previewNode->addChild(this->previewStalactite100);
	this->previewNode->addChild(this->previewStalactite200);
	this->previewNode->addChild(this->previewStalactite400);
	this->assemblyTextNode->addChild(this->eax100Height);
	this->assemblyTextNode->addChild(this->eax200Height);
	this->assemblyTextNode->addChild(this->eax400Height);
}

HackablePreview* StalactiteSetSpeedPreview::clone()
{
	return StalactiteSetSpeedPreview::create();
}

void StalactiteSetSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;
	const float topOffset = 48.0f;

	this->previewStalactite100->setPosition(Vec2(-96.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewStalactite400->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewStalactite200->setPosition(Vec2(96.0f, HackablePreview::PreviewRadius - offset - topOffset));

	this->previewStalactite100->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite100->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 4.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite100->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewStalactite200->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite200->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite200->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewStalactite400->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite400->getPositionX(), -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewStalactite400->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);
}

void StalactiteSetSpeedPreview::initializePositions()
{
	super::initializePositions();

	this->eax100Height->setPosition(Vec2(-112.0f, HackablePreview::PreviewRadius - 48.0f));
	this->eax400Height->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius));
	this->eax200Height->setPosition(Vec2(112.0f, HackablePreview::PreviewRadius - 48.0f));
}
