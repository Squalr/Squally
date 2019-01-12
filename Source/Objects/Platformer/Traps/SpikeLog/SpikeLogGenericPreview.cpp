#include "SpikeLogGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

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
	this->previewSpikeLog = Sprite::create(ObjectResources::Traps_SpikeLog_PreviewSpikeLog);

	this->previewSpikeLog->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewSpikeLog);
}

HackablePreview* SpikeLogGenericPreview::clone()
{
	return SpikeLogGenericPreview::create();
}

void SpikeLogGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewSpikeLog->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));

	this->previewSpikeLog->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}
