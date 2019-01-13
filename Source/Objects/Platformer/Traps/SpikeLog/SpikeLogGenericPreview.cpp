#include "SpikeLogGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikeLogGenericPreview* SpikeLogGenericPreview::create()
{
	SpikeLogGenericPreview* instance = new SpikeLogGenericPreview();

	instance->autorelease();

	return instance;
}

SpikeLogGenericPreview::SpikeLogGenericPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);

	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.08f, 0.0f);
	this->previewSpikedLog->setScale(0.25f);

	this->previewNode->addChild(this->previewSpikedLog);
}

HackablePreview* SpikeLogGenericPreview::clone()
{
	return SpikeLogGenericPreview::create();
}

void SpikeLogGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewSpikedLog->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius / 2.0f));

	/*
	this->previewSpikedLog->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);*/
}
